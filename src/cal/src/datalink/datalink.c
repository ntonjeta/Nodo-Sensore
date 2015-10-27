/**
 ******************************************************************************
 * @file    datalink.c
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    28/giu/2015
 * @brief   TODO: brief for datalink.c
 ******************************************************************************
 */

/* Includes ********************************************************************/
#include "conf/cal_conf.h"
#include "datalink.h"
#include "datalink_utils.h"
#include "utils/frame_utils.h"
#include "utils/timer.h"

/**
 * @addtogroup CAL_Module
 * @{
 */

/**
 * @addtogroup CAL_DATALINK_Module Livello Datalink
 * @{
 */

/* Private Constants ***********************************************************/
/* Private Macros **************************************************************/

/**
 * @defgroup CAL_DATALINK_Private_Macros Private Macros
 * @brief Macro private
 * @{
 */

#define _dlSetTick(seqNumber,tick)				tickMap[seqNumber] = tick
#define _dlGetTick(seqNumber)					tickMap[seqNumber]
#define _dlGetNumRetry(seqNumber)				numRetryMap[seqNumber]
#define _dlSetNumRetry(seqNumber,numRetry)		numRetryMap[seqNumber] = numRetry

/**
 * @}
 */

/* Private Types ***************************************************************/
/* Private Variables ***********************************************************/

/**
 * @defgroup CAL_DATALINK_Private_Variables Private Variables
 * @brief Variabili private
 * @{
 */

DL_FrameQueue* dlTxQueue[GET_MAX_INTERFACES()];
DL_FrameQueue* dlRxQueue;
DL_FrameQueue* dlNotificationQueue;

static uint8_t dlInterfaceReady[GET_MAX_INTERFACES()];

static DL_SeqNumber_Type seqNumberMap[DL_SEQ_NUMBER_MAP_SIZE];
static uint8_t numRetryMap[DL_SEQ_NUMBER_MAP_SIZE];
static int16_t tickMap[DL_SEQ_NUMBER_MAP_SIZE];

static CAL_Option_Type dlTempInterfaceStatus[GET_MAX_INTERFACES()];
static CAL_Option_Type dlInterfaceAttachStatus[GET_MAX_INTERFACES()];

DL_Frame* dlTxStagingArray[GET_MAX_INTERFACES()];
DL_Frame* dlWaitingForAckStagingArray[DL_SEQ_NUMBER_MAP_SIZE];

static DL_SeqNumber_Type lastUsedSeqNumber;
static DL_SeqNumber_Type seqNumberCounter;

static uint8_t timerScanCounter CAL_UNUSED_FUNCTION;

//static uint32_t receivedPacketCounter;

/**
 * @}
 */

/* Private Functions ***********************************************************/
static void _dlEnqueueAndTryToSend(DL_Frame *, CAL_InterfaceNumber) CAL_UNUSED_FUNCTION;

/* Declaration *****************************************************************/

extern void receivedPacketCallback(CAL_InterfaceNumber, uint8_t*, uint16_t);
extern void interfaceAttachedCallback(CAL_InterfaceNumber);
extern void interfaceDetachedCallback(CAL_InterfaceNumber);
extern void sendErrorCallback(CAL_InterfaceNumber, uint8_t*,uint16_t);
extern void sentPacketCallback(CAL_InterfaceNumber, uint8_t*,uint16_t);

uint8_t _dlTxFrameQueueIsEmpty(CAL_InterfaceNumber ifx);
void _dlSeqNumberAcked(DL_SeqNumber_Type seqNumber);

/**
 * @defgroup CAL_DATALINK_Private_Functions Private Functions
 * @brief Funzioni private
 * @{
 */

/* Getter and Setter */

DL_Frame* _dlGetFrameFromWaitingStage(DL_SeqNumber_Type seqNumber)
{
	return dlWaitingForAckStagingArray[seqNumber];
}

DL_Frame* _dlGetFrameFromTxStage(DL_SeqNumber_Type seqNumber)
{
	return dlTxStagingArray[seqNumber];
}

DL_SeqNumber_Type _dlGetSequenceNumber(CAL_InterfaceNumber ifx)
{
	return seqNumberMap[ifx];
}

DL_InterfaceReady_Status _dlGetInterfaceReadyStatus(CAL_InterfaceNumber ifx)
{
	return dlInterfaceReady[ifx];
}

void _dlSetInterfaceReadyStatus(CAL_InterfaceNumber ifx,
		DL_InterfaceReady_Status newStatus)
{
	dlInterfaceReady[ifx] = newStatus;
}

/* Rollback utilities */

void _dlFreeResources(int16_t seqNumber, DL_Frame_Header *header,
		DL_Frame *frame)
{
	if (seqNumber >= 0)
		_dlSeqNumberAcked(seqNumber); //Frees the SN

	//Frees resources

	calLogInt(CAL_LOG_DEBUG, "_dlFreeResources", "HEADER-FREED-B", (uint16_t)HEADER_LENGTH*sizeof(uint8_t));
	calFree(header);

	if (frame != 0)
	{
		if(frame->data!=0)
		{
			calLogInt(CAL_LOG_DEBUG, "_dlFreeResources", "PAYLOAD-FREED ", frame->data[DL_NUMCHUNKS_FIELD]*CHUNK_LENGTH*sizeof(uint8_t));
			calFree(frame->data);
		}
		calFree(frame);
		calLogInt(CAL_LOG_DEBUG, "_dlFreeResources", "FRAME-FREED ", sizeof(CAL_InterfaceNumber)+sizeof(uint8_t*));
	}
}

/* Frame Handling Utilities */

/**
 * @brief	Estrazione del pacchetto da una frame di input
 * @param	frame: puntatore della frame da cui estrarre l'header.
 * @param	header: puntatore all'header della frame.
 * @retval	puntatore al pacchetto estratto:
 * 			@arg	0 : errore di estrazione (risorse non allocate);
 * 			@arg	ANY: pacchetto estratto correttamente.
 */
uint8_t* _dlGetPacketFromFrame(DL_Frame *frame)
{

	DL_NumChunks_Type numChunks = frame->data[DL_NUMCHUNKS_FIELD];
	DL_Padding_Type padding = frame->data[DL_PADDING_FIELD];
	//The packetLength is: Total Length - Header - Padding [byte]
	uint16_t packetLength = numChunks * CHUNK_LENGTH - HEADER_LENGTH - padding;

	uint8_t *packet = 0;
	packet = calMalloc(sizeof(uint8_t) * packetLength);
	if (packet == 0)
		return 0;

	uint8_t *ptr = frame->data + HEADER_LENGTH;

	//Get only the packet ( = the payload of the frame)
	memcpy(packet, ptr, packetLength);

	calLogInt(CAL_LOG_DEBUG, "_dlGetPacketFromFrame", "PACKET-EXTRACTED-B ", packetLength);
	return packet;
}

/**
 * @brief	Predispone il payload della frame da inviare (header+packet+padding).
 *
 * @param	framePayload: area 'data' della frame (precedentemente allocata);
 * @param	header: puntatore all'header da inserire;
 * @param	headerLength: dimensione header in byte;
 * @param	packet: puntatore al pacchetto da inviare;
 * @param	packetLength: dimensione pacchetto in byte;
 * @param	paddingLength: dimensione padding della frame in byte.
 * @param	calculateCRC: indica se calcolare (CAL_YES) o meno (CAL_NO) il CRC della frame.
 *
 * @retval	none.
 */
void _dlPrepareFrameData(uint8_t *framePayload, DL_Frame_Header *header,
		uint8_t headerLength, uint8_t* packet, uint16_t packetLength,
		uint8_t paddingLength, CAL_Option_Type calculateCRC)
{
	//Copy the DL_Frame_Header in the first HEADER_LENGTH Byte
	framePayload[DL_FTYPE_FIELD] = header->fType;
	framePayload[DL_SEQNUMBER_FIELD] = header->seqNumber;
	framePayload[DL_NUMCHUNKS_FIELD] = header->numChunks;
	framePayload[DL_PADDING_FIELD] = header->padding;
	framePayload[DL_RESERVED_FIELD] = header->reserved;
	framePayload[DL_CHECKSUM_FIELD] = header->checksum;

	uint8_t *ptr = framePayload + headerLength; //now *ptr is located on the Payload Field

	//Copy the payload (the packet received from Upper Layer) in the [HEADER_LENGTH..packetLength-1] bytes of DL_Frame
	if (packetLength > 0 && packet != 0)
		memcpy(ptr, packet, packetLength);

	//Copy a clean padding in the last 'padding' bytes
	if (paddingLength > 0)
	{
		uint8_t tempPadding[paddingLength];
		memset(&tempPadding, 0, paddingLength);
		ptr += packetLength; //now *ptr is located on Padding Field
		memcpy(ptr, &tempPadding, paddingLength);
	}

	if (calculateCRC == CAL_YES)
		frameCRCCreate(framePayload, header->numChunks * CHUNK_LENGTH);
}
/**
 * @brief	Predispone l'invio di una frame (frameOut) sull'interfaccia ifxIn
 * 			estraendola dalla coda di invio.
 *
 * @param	ifxIn: interfaccia di invio;
 * @param	frameOut: puntatore alla frame estratta dalla coda di invio;
 * @param	numChunksOut: numChunks che compongono la frame.
 *
 * @retval	none.
 */
DL_Frame* _dlPrepareToSendFrameOverInterface(CAL_InterfaceNumber ifxIn)
{
	DL_Frame *frameOut = NULL;
	//First check if there are other Frame in the queue which can be sent
	if (_dlTxFrameQueueIsEmpty(ifxIn) == 1)
	{
		_dlSetInterfaceReadyStatus(ifxIn, DL_READY);
		return 0;
	}
	else
	{
		frameOut = dequeueFrame(dlTxQueue[ifxIn]);

		if (frameOut == 0)
			return 0;

		//Set the interface IFx as "Not Ready"
		dlInterfaceReady[ifxIn] = DL_NOT_READY;

		//Save the Frame which are going to be sent into TxStaging Area
		dlTxStagingArray[ifxIn] = frameOut;


		calLogInt(CAL_LOG_DEBUG, "_dlPrepareToSendFrameOverInterface", "FRAME-IN-TX-AREA-NUM", ifxIn);
		return frameOut;
	}
}
/**
 * @brief	Estrae l'header da una frame di input
 * @param	frame: puntatore della frame da cui estrarre l'header.
 * @retval	puntatore all'header estratto:
 * 			@arg	0 : errore di estrazione (risorse non allocate);
 * 			@arg	ANY: header estratto correttamente.
 */
DL_Frame_Header *_dlGetHeaderFromFrame(DL_Frame *frame)
{
	//Copy the Received Header
	DL_Frame_Header *header = 0;
	header = calMalloc(sizeof(DL_Frame_Header));
	if (header == 0)
		return 0;

	header->fType = frame->data[DL_FTYPE_FIELD];
	header->seqNumber = frame->data[DL_SEQNUMBER_FIELD];
	header->numChunks = frame->data[DL_NUMCHUNKS_FIELD];
	header->padding = frame->data[DL_PADDING_FIELD];
	header->reserved = frame->data[DL_RESERVED_FIELD];
	header->checksum = frame->data[DL_CHECKSUM_FIELD];

	return header;
}

/**
 * @brief	Funzione che inizializza una DL_Frame_Header, ossia un header per una frame.
 *
 * @param	type: tipo della frame;
 * @param	seqNumber: sequence number;
 * @param	reserved: valore del campo reserved;
 * @param	headerLength: lunghezza dell'header;
 * @param	packetLength: lunghezza del pacchetto che l'header dovr� considerare;
 * @param	chunkLength, dimensione dei chunk (unit� di invio atomica plcp).
 *
 * @retval	puntatore all'header inizializzato.
 * 			@arg	0 : errore di inizializzazione (risorse non allocate);
 * 			@arg	ANY: header inizializzato correttamente.
 */
DL_Frame_Header* _dlPrepareHeader(DL_Frame_Type type,
		DL_SeqNumber_Type seqNumber, DL_Reserved_Type reserved,
		uint8_t headerLength, uint16_t packetLength, uint16_t chunkLength,
		CAL_Option_Type calculateCRC)
{
	DL_Frame_Header* dlHeader = 0;
	dlHeader = calMalloc(sizeof(DL_Frame_Header));

	//Checks if the Header Malloc has been executed succesfully
	if (dlHeader == 0)
		return 0;

	// Set the Common field of the Frame Header
	dlHeader->seqNumber = seqNumber;
	dlHeader->reserved = reserved;
	dlHeader->fType = type;

	switch (type)
	{
	case DL_DATA:
	{
		//The initial Frame Length is PacketLen + HeaderLen, after we check if we need padding.
		uint16_t length = packetLength + headerLength;
		if (calculateCRC == CAL_YES)
			length += CRC_LENGTH; //Add 4 bytes for CRC

		//Compute the Num of Chunks, the padding and the additional DL_Frame Length.
		dlHeader->numChunks = length / chunkLength; // compute the integer division
		uint16_t dataChunkOverflow = length % chunkLength; // get the optional overflow
		dlHeader->padding = 0; // the initial paddingLength is 0

		// compute the paddingLength only if there is an overflow
		if (dataChunkOverflow > 0)
		{
			// compute the paddingLength (for the last chunk)
			dlHeader->padding = chunkLength - dataChunkOverflow;

			if (calculateCRC == CAL_YES)
				dlHeader->padding += CRC_LENGTH;

			// because of the overflow, we need another final chunk
			dlHeader->numChunks++;
		}
	}
		break;

	case DL_ACK:
	{
		dlHeader->numChunks = 1;
		dlHeader->padding = chunkLength - headerLength;
	}
		break;

	case DL_WELCOME:
	{
		dlHeader->numChunks = 1;
		dlHeader->padding = chunkLength - headerLength;

	}
		break;

	case DL_BYE:
	{
		dlHeader->numChunks = 1;
		dlHeader->padding = chunkLength - headerLength;
	}
		break;
	default:
		break;
	}

	//Sets the Checksum
	frameHeaderChecksumCreate(dlHeader);


	calLogInt(CAL_LOG_DEBUG, "_dlPrepareHeader", "HEADER-ALLOCATED-B",(uint16_t)HEADER_LENGTH);
	return dlHeader;

}
/**
 * @brief	Funzione che inizializza una DL_Frame allocandone le risorse
 * @param	ifx: interfaccia sulla quale sar� inviata la frame;
 * @param	length: lunghezza del campo 'data' della frame (payload);
 * @retval	frame, puntatore alla frame inizializzata.
 * 			@arg	0 : errore di inizializzazione (risorse non allocate);
 * 			@arg	ANY: frame inizializzata correttamente.
 */
DL_Frame* _dlPrepareFrame(CAL_InterfaceNumber ifx, uint16_t length)
{

	//Malloc the DL_frame which will be sent
	DL_Frame* frame = 0;
	frame = calMalloc(sizeof(DL_Frame));

	if (frame == 0)
		return 0;

	//Set the Ifx Field of the DL_Frame which will be sent.
	frame->ifx = ifx;

	//Malloc the data field of the frame (with the right length).
	frame->data = calMalloc(length * sizeof(uint8_t));

	if (frame->data == 0)
	{
		calFree(frame);
		return 0;
	}

	calLogInt(CAL_LOG_DEBUG, "_dlPrepareFrame", "FRAME-ALLOCATED-B",sizeof(CAL_InterfaceNumber)+sizeof(uint8_t));
	return frame;
}

/* Queue Utilities */
uint8_t _dlTxFrameQueueIsEmpty(CAL_InterfaceNumber ifx)
{
	return frameQueueLength(dlTxQueue[ifx]) == 0;
}

void _dlEnqueueTxFrameQueue(CAL_InterfaceNumber ifx, DL_Frame *frame)
{
	enqueueFrame(dlTxQueue[ifx], frame);
}

/*
 *  Frame sending and receiving utilities
 */
/**
 * @brief	Funzione che 'occupa' un sequence number per una frame
 * 			che deve essere inviata.
 * @param	none
 * @retval	seqNumber, il cui valore pu� essere uno tra i seguenti
 * 			@arg	-1 : nessun seq. number disponibile;
 * 			@arg	0..DL_SEQ_NUMBER_MAP_SIZE-1 : sequence number valido ottenuto.
 */
int16_t _dlGetAvailableSeqNumber()
{
	//Check if all sequence numbers has been used
	if (seqNumberCounter >= DL_SEQ_NUMBER_MAP_SIZE - 1)
	{
		calLogInt(CAL_LOG_WARNING, "_dlSeqNumberAcked", "SEQ-NUM-UNAVAILABLE", 0);
		return -1;
	}
	uint8_t flag = 1;
	while (flag != 0)
	{
		lastUsedSeqNumber = (lastUsedSeqNumber + 1) % DL_SEQ_NUMBER_MAP_SIZE;
		//Check if the seq_number is available
		if (seqNumberMap[lastUsedSeqNumber] == AVAILABLE)
		{
			//Set as "not Available" the seq_number
			seqNumberMap[lastUsedSeqNumber] = NOT_AVAILABLE;
			flag = 0;
			seqNumberCounter++;
			calLogInt(CAL_LOG_DEBUG, "_dlGetAvailableSeqNumber", "SEQ-NUM-ALLOCATED", lastUsedSeqNumber);
		}
	}

	return (int16_t) lastUsedSeqNumber;
}
/**
 * @brief	Funzione di "seqNumber riscontrato" (Frame riscontrata) sull'interfaccia ifx.
 * 			Se la frame � una frame Dati oppure di Welcome questa viene
 * 			spostata nella seconda area di staging (WaitingForAck Area)
 * 			in quanto l'effettivo successo dell'invio lo si ha quando
 * 			la frame viene riscontrata con un ACK.
 * @param	ifx: interfaccia sulla quale la frame � stata inviata.
 * @retval	none.
 */
void _dlSeqNumberAcked(DL_SeqNumber_Type seqNumber)
{
	//Free the WaitingForAck staging area related to the Acked SeqNumber.
	DL_Frame *frame = dlWaitingForAckStagingArray[seqNumber];
	if (frame != 0)
	{
		if(frame->data!=0)
			calFree(frame->data);
		calFree(frame);
		dlWaitingForAckStagingArray[seqNumber] = 0;
		calLogInt(CAL_LOG_DEBUG, "_dlSeqNumberAcked", "WAIT-AREA-FREED-NUM ", seqNumber);
	}

	seqNumberMap[seqNumber] = AVAILABLE;
	--seqNumberCounter;

	calLogInt(CAL_LOG_DEBUG, "_dlSeqNumberAcked", "SEQ-NUM-DEALLOCATED", seqNumber);
}

/**
 * @brief	Funzione di "Frame inviata" sull'interfaccia ifx.
 * 			Se la frame � una frame Dati oppure di Welcome questa viene
 * 			spostata nella seconda area di staging (WaitingForAck Area)
 * 			in quanto l'effettivo successo dell'invio lo si ha quando
 * 			la frame viene riscontrata con un ACK.
 * @param	ifx: interfaccia sulla quale la frame � stata inviata.
 * @retval	none.
 */
void _dlFrameSent(CAL_InterfaceNumber ifx)
{
	DL_Frame *frame = dlTxStagingArray[ifx];
	DL_Frame_Type type = frame->data[DL_FTYPE_FIELD];

	//If the frame SENT is a Data Frame or WELCOME frame => put the frame into WaitingForAck Staging Area
	if (type == DL_DATA || type == DL_WELCOME)
	{
		DL_SeqNumber_Type seqNumber = frame->data[DL_SEQNUMBER_FIELD];
		dlWaitingForAckStagingArray[seqNumber] = frame;
		calLogInt(CAL_LOG_DEBUG, "_dlFrameSent", "FRAME-MOVED-WAITING-AREA-IFx ", ifx);
	}
	else
	{
		//if the frame sent is  BYE Frame => disable the interface
		//(because a BYE Frame is allways sent when the upper layer calls "dlDisableInterface(ifx)
		if (type == DL_BYE)
		{
			//Frees ALL resources allocated By the interface IFx which will be disable soon.
			uint16_t i = 0;
			DL_Frame *temp;
			while (i < DL_SEQ_NUMBER_MAP_SIZE)
			{
				calLogInt(CAL_LOG_DEBUG, "_dlFrameSent", "BYE-SENT-FREEING-RES-IFx ", ifx);
				temp = dlWaitingForAckStagingArray[i++];
				if (temp != 0 && temp->ifx == ifx)
					_dlFreeResources(i, 0, 0);
			}

			dlInterfaceAttachStatus[ifx]=CAL_NO;
			plcpDisableInterface(ifx);
		}

		if(frame->data!=0)
			calFree(frame->data);
		calFree(frame); //You can free the TxStagingArea
	}

}

/**
 * @brief	Funzione di valutazione del parametro numRetry
 * 			al fine di valutare se reinoltrare la frame (numRetry>=0)
 * 			oppure notificare il livello superiore circa l'invio fallito.
 * @param	frame: puntatore alla frame da valutare.
 * @param	seqNumber: sequence number associato alla frame.
 * @retval	none.
 */
void _dlEvaluateNumRetry(DL_Frame* frame, DL_SeqNumber_Type seqNumber)
{
	DL_Status status = DL_ERROR;
	uint8_t numRetry = _dlGetNumRetry(seqNumber);
	if (numRetry > 0)
	{
		_dlSetTick(seqNumber, DL_NUM_TICK_MAX);
		_dlSetNumRetry(seqNumber, numRetry - 1);
#if CAL_USE_OS == 0
		status = DL_OK;

		calLogInt(CAL_LOG_INFORMATIONAL, "_dlEvaluateNumRetry", "FRAME-RETRANSMIT-SEQ-NUMBER ", seqNumber);
		_dlEnqueueAndTryToSend(frame, frame->ifx);

#else
		if (_dlTaskEnqueueAndTryToSend(frame->ifx, frame) != 0)	//Safe Behaviour when sem_handle == NULL.
			status = DL_OK;
#endif

	}

	if (status == DL_ERROR)
	{

		if (frame->data[DL_FTYPE_FIELD] == DL_DATA)	//Notify only if the frame is a data frame.
		{

#if CAL_USE_OS == 0
			frame->data[DL_FTYPE_FIELD] = DL_SENT_FAILED;
			enqueueFrame(dlNotificationQueue, frame);
#else
			_dlTaskNotifySendingFailure(frame);
#endif
		}
		else

			//Frees the Resources (so frees the SN and the WaitingForAck area);
			_dlFreeResources(seqNumber, 0, 0);

	}
}

/**
 * @brief	Funzione di scansione della TxStaging Area al fine di determinare
 * 			quale frame deve essere rinviata perch� � scaduto il timeout
 * 			(frame non riscontrata entro il timeout definito).
 * @retval	none.
 */
void _dlScanWaitingStagingArea()
{

	calLogInt(CAL_LOG_DEBUG, "_dlScanWaitingStagingArea", "FUN-CALLED", 0);
	uint32_t i = 0;
	DL_Frame* frame;
	DL_SeqNumber_Type seqNumber = -1;
	int16_t tick;
	while (i < DL_SEQ_NUMBER_MAP_SIZE)
	{
		frame = dlWaitingForAckStagingArray[i];
		if (frame != 0)
		{
			seqNumber = frame->data[DL_SEQNUMBER_FIELD];
			tick = (int16_t) _dlGetTick(seqNumber);
			if (tick >= 0)
				_dlSetTick(seqNumber, tick - 1);
			else
				_dlEvaluateNumRetry(frame, seqNumber);
		}
		++i;

	}
}

/**
 * @brief	Frame di Ack ricevuta.
 * @param	frame: puntatore alla frame ricevuta.
 * @param	headder: puntatore all'header della frame ricevuta.
 * @retval	none.
 */
void _dlReceivedAckFrame(DL_Frame *frame)
{
	//Get the 'Acked' Frame
	DL_SeqNumber_Type seqNumber = frame->data[DL_SEQNUMBER_FIELD];
	DL_Frame *frameAcked = _dlGetFrameFromWaitingStage(seqNumber);

	switch (frameAcked->data[DL_FTYPE_FIELD])
	//Check the type
	{
	case DL_DATA://The frame acked it's a data frame -> notify through "Sent Callback"
	{

		calLogInt(CAL_LOG_DEBUG, "_dlReceivedAckFrame", "ACKED-DATA-FRAME-IFx ", frame->ifx);
		frameAcked->data[DL_FTYPE_FIELD] = DL_SENT;
#if (CAL_USE_OS == 0)
		enqueueFrame(dlNotificationQueue,frameAcked);
#else
		_dlTaskNotifySentFrame(frameAcked);
#endif

		//Free header, data and frame (ACK Frame just received)
		// (also clean the WaitingForAck Area, so the FrameAcked)
		_dlFreeResources(-1, 0, frame);
	}
		break;

	case DL_WELCOME:			// notify through "Interface Attached Callback"
	{
		calLogInt(CAL_LOG_INFORMATIONAL, "_dlReceivedAckFrame", "ATTACHED-IFx ", frame->ifx);
		dlInterfaceAttachStatus[frame->ifx]=CAL_YES;
		interfaceAttachedCallback(frame->ifx);
		//Free header, data and frame (ACK Frame just received)
		// (also clean the WaitingForAck Area, so the FrameAcked)
		_dlFreeResources(seqNumber, 0, frame);
	}
		break;

	default:{
		_dlFreeResources(-1,0,frame);} break;
	}

}

/**
 * @brief	Frame di BYE ricevuta.
 * @param	frame: puntatore alla frame ricevuta.
 * @param	headder: puntatore all'header della frame ricevuta.
 * @retval	none.
 */
void _dlReceivedByeFrame(DL_Frame *frame)
{

	CAL_InterfaceNumber ifx = frame->ifx;
	//Frees resources (The BYE Frame is never located into WaitingForAck Area)
	_dlFreeResources(-1,0,frame);


	calLogInt(CAL_LOG_INFORMATIONAL, "_dlReceivedByeFrame", "DETACHED-IFx ", ifx);
	dlInterfaceAttachStatus[ifx]=CAL_NO;
	interfaceDetachedCallback(ifx);
}

/**
 * @brief	Frame di Dati ricevuta.
 * @param	frame: puntatore alla frame ricevuta.
 * @param	headder: puntatore all'header della frame ricevuta.
 * @retval	none.
 */
void _dlReceivedDataFrame(DL_Frame *frame)
{
	//Checks the CRC of the DATA Frame
	CAL_Option_Type pass = CAL_YES;
	DL_NumChunks_Type numChunks = frame->data[DL_NUMCHUNKS_FIELD];
	if (crcCheckState() == 1)
		pass = frameCRCCheck(frame->data, numChunks * CHUNK_LENGTH);

	if (pass == CAL_YES)
	{
		DL_Padding_Type padding = frame->data[DL_PADDING_FIELD];
		//Extract the Packet (Frame Data Payload)
		uint8_t *packet = _dlGetPacketFromFrame(frame);
		uint16_t packetLength = numChunks * CHUNK_LENGTH - HEADER_LENGTH
				- padding;

		CAL_InterfaceNumber ifx = frame->ifx;
		DL_SeqNumber_Type seqNumber = frame->data[DL_SEQNUMBER_FIELD];

		//Now Enqueue the DL_ACK Frame
#if CAL_USE_OSE == 0
		_dlSendAckFrame(ifx, seqNumber);
#else
		_dlTaskSendAckFrame(ifx,seqNumber);
#endif

		//TODO: Sviluppi futuri (reset dopo N pacchetti ricevuti)
		//receivedPacketCounter++;
		//Call the Received Packet From callback

		calLogInt(CAL_LOG_INFORMATIONAL, "_dlReceivedDataFrame", "PACKET-RECEIVED-IFx ", ifx);
		receivedPacketCallback(ifx, packet, packetLength);

		//Frees the packet (the upper layers MUST memcpy it into callback)
		calFree(packet);
		calLogInt(CAL_LOG_DEBUG, "_dlReceivedDataFrame", "PACKET-FREED-B ", packetLength);
		//Free the frame received
		_dlFreeResources(-1,0,frame);
	}
	else
	{
		calLogInt(CAL_LOG_WARNING, "_dlReceivedDataFrame", "CRC-CHECK-FAILED ",0);
		//Simply Frees the frame received
		_dlFreeResources(-1,0,frame);
	}
}

/**
 * @brief	Frame di Welcome ricevuta.
 * @param	frame: puntatore alla frame ricevuta.
 * @param	headder: puntatore all'header della frame ricevuta.
 * @retval	none.
 */
void _dlReceivedWelcomeFrame(DL_Frame *frame)
{
	CAL_InterfaceNumber ifx = frame->ifx;
	DL_SeqNumber_Type seqNumber = frame->data[DL_SEQNUMBER_FIELD];

	//Send an ACK for the frame
#if CAL_USE_OSE == 0
	_dlSendAckFrame(ifx, seqNumber);
#else
	_dlTaskSendAckFrame(ifx,seqNumber);
#endif

	//Frees resources (the received header and the received Frame).
	_dlFreeResources(-1,0,frame);

	//Notify attach
	dlInterfaceAttachStatus[ifx]=CAL_YES;
	interfaceAttachedCallback(ifx);
}

/**
 * @brief	Funzione di invio di una frame di Ack.
 * @param	IFx: numero interfaccia.
 * @param	seqNumber: sequence number da riscontrare tramite l'invio dell'ACK.
 * @retval	none.
 */
void _dlSendAckFrame(CAL_InterfaceNumber ifx, DL_SeqNumber_Type seqNumber)
{
	DL_Frame_Header *header = NULL;
	DL_Frame *frame = NULL;
	DL_Status status = DL_ERROR;
	header = calMalloc(sizeof(DL_Frame_Header));
	if (header != 0)
	{
		header = _dlPrepareHeader(DL_ACK, seqNumber, CAL_FIELD_RESERVED,
		HEADER_LENGTH, 0, CHUNK_LENGTH, CAL_NO);

		frame = _dlPrepareFrame(ifx, CHUNK_LENGTH);
		if (frame != 0 && frame->data != 0)
		{
			//Prepare the DL_ACK Frame (no packet-payload with a null packetLenght)
			_dlPrepareFrameData(frame->data, header, HEADER_LENGTH, 0, 0,
					header->padding, CAL_NO);
			calLogInt(CAL_LOG_DEBUG, "_dlSendAckFrame", "FRAME-PAYLOAD-ALLOCATED-B", (uint16_t)(header->numChunks * CHUNK_LENGTH));


			calFree(header);
			calLogInt(CAL_LOG_DEBUG,"_dlSendAckFrame","HEADER-FREED-B",HEADER_LENGTH);
			calLogInt(CAL_LOG_DEBUG,"_dlSendAckFrame","SENDING-ACK-IFx",ifx);

#if CAL_USE_OS == 0
			status = DL_OK;
			_dlEnqueueAndTryToSend(frame, ifx);
#else
			if (_dlTaskEnqueueAndTryToSend(ifx, frame) != 0)
				status = DL_OK;
			/*
			 * The return values is handled only for freeing the resources because if  sem_handle == NULL doesn't send the ACK.
			 * It isn't a problem because the counterpart will perform another trasnfer of the same frame.
			 *
			 */
#endif
		}
	}

	if (status == DL_ERROR)
		_dlFreeResources(-1, 0, frame); //seqNumber=-1 because we don't manage it here. The frame is that allocated in this function.
}

/**
 * @brief	Funzione di invio di una frame di Welcome.
 * @param	IFx: numero interfaccia.
 * 			Pu� assumere i seguenti valori:
 * 			@arg IFx valore singolo: invio BYE attraverso interfaccia x;
 * 			@arg IF_ALL: invio BYE su tutte le interfacce.
 * @retval	none.
 */
void _dlSendWelcomeFrame(CAL_InterfaceNumber ifx)
{
	DL_Status status;
	DL_Frame_Header *header;
	DL_Frame *frame;
	int16_t seqNumber;

	CAL_InterfaceNumber i = ifx;
	int maxIter = i + 1;
	if (ifx == IF_ALL)
	{
		i = 0;
		maxIter = GET_MAX_INTERFACES();
	}

	do
	{
		status = DL_ERROR;
		header = 0;
		frame = 0;
		seqNumber = -1;

		if (plcpGetInterfaceStatus(i) == CAL_YES)
		{
			seqNumber = _dlGetAvailableSeqNumber();
			if (seqNumber >= 0)
			{
				//Save the numRetry preferences for the frame which will be sent
				_dlSetNumRetry(seqNumber, DL_WELCOME_NUM_RETRY);

				//Set the tick count
				_dlSetTick(seqNumber, DL_NUM_TICK_MAX);
				header = _dlPrepareHeader(DL_WELCOME, seqNumber,
						CAL_FIELD_RESERVED,
						HEADER_LENGTH, 0, CHUNK_LENGTH, CAL_NO);
				if (header != 0)
				{
					frame = _dlPrepareFrame(i, CHUNK_LENGTH);

					_dlPrepareFrameData(frame->data, header, HEADER_LENGTH, 0,
							0, header->padding, CAL_NO);

					calLogInt(CAL_LOG_DEBUG,"_dlSendWelcomeFrame","FRAME-PAYLOAD-ALLOCATED-B",header->numChunks*CHUNK_LENGTH);

					calFree(header);
					calLogInt(CAL_LOG_DEBUG,"_dlSendWelcomeFrame","HEADER-FREED-B",HEADER_LENGTH);

					calLogInt(CAL_LOG_INFORMATIONAL,"_dlSendWelcomeFrame","SENDING-WELCOME-IFx",i);
#if CAL_USE_OS == 0
					status = DL_OK; //All checks are passed
					_dlEnqueueAndTryToSend(frame, i);
#else
					if (_dlTaskEnqueueAndTryToSend(i, frame) == 0)
					{
						plcpDisableInterface(i); //If sem_Handle==0 => disable the interface
					}
					else
						status = DL_OK; //All checks are passed! Status OK
#endif
				}
			}
		}

		if (status == DL_ERROR)
			_dlFreeResources(seqNumber, header, frame);

		i++;
	} while (i < maxIter);

}

/**
 * @brief	Funzione di invio di una frame di BYE.
 * @param	IFx: numero interfaccia.
 * 			Pu� assumere i seguenti valori:
 * 			@arg IFx valore singolo: invio BYE attraverso interfaccia x;
 * 			@arg IF_ALL: invio BYE su tutte le interfacce.
 * @retval	none.
 */
void _dlSendByeFrame(CAL_InterfaceNumber ifx)
{
	DL_Frame_Header *header = 0;
	header=_dlPrepareHeader(DL_BYE, 0, CAL_FIELD_RESERVED,
	HEADER_LENGTH, 0, CHUNK_LENGTH, CAL_NO);

	if (header != 0)
	{
		calLogInt(CAL_LOG_DEBUG,"_dlSendByeFrame","HEADER-ALLOCATED-B",HEADER_LENGTH);

		CAL_InterfaceNumber i = ifx;
		int maxIter = i + 1;
		if (ifx == IF_ALL)
		{
			i = 0;
			maxIter = GET_MAX_INTERFACES();
		}

		DL_Frame *frame;
		//Se IFx è singolo allora verrà  eseguita una sola iterazione, altrimenti ne verranno eseguite NUM_INTERFACES.
		do
		{
			frame = 0;
			//Prepare the BYE Frame which is only one chunk
			frame = _dlPrepareFrame(i, CHUNK_LENGTH);
			if (frame != 0 && frame->data != 0)
			{

				calLogInt(CAL_LOG_DEBUG,"_dlSendByeFrame","FRAME-PAYLOAD-ALLOCATED-B",(header->numChunks * CHUNK_LENGTH));
				_dlPrepareFrameData(frame->data, header, HEADER_LENGTH, 0, 0,
						header->padding, CAL_NO);
				calLogInt(CAL_LOG_INFORMATIONAL,"_dlSendByeFrame","SENDING-BYE-IFx",i);

#if CAL_USE_OS == 0
				_dlEnqueueAndTryToSend(frame, i);
#else
				_dlTaskEnqueueAndTryToSend(i, frame);
				/*
				 * doesn't matter if sem_handle == 0 because the counterpart's Network layer
				 *  will understand EVENTUALLY that IFx is unavailable (we hope :D)
				 */
#endif
			}
			else if (frame != 0) //Frees resources (safe behaviour);
				_dlFreeResources(-1,0,frame);

			i++;
		} while (i < maxIter);

		calFree(header);
		calLogInt(CAL_LOG_DEBUG,"_dlSendByeFrame","HEADER-FREED-B",HEADER_LENGTH);
	}

	//When receives an Upstream CAL_SENT message check if it is a BYE and call plcpDisableInterface(ifx).
	//(Disable REALLY the interface ifx);

}

/**
 * @brief	Funzione di smistamento di una frame ricevuta con controllo della checksum.
 * @param	frame: puntatore alla frame ricevuta.
 * @retval	none.
 */
void _dlSwitchReceivedFrame(DL_Frame *frame)
{
	DL_Frame_Type type = frame->data[DL_FTYPE_FIELD];
	calLogInt(CAL_LOG_INFORMATIONAL,"_dlSwitchReceivedFrame","FRAME-RECEIVED-TYPE",(uint16_t)type);
	//Check the FType Field of the Header and perform the right operations
	switch (type)
	{
	case DL_ACK:
		_dlReceivedAckFrame(frame);
		break;
	case DL_DATA:
		_dlReceivedDataFrame(frame);
		break;
	case DL_WELCOME:
		_dlReceivedWelcomeFrame(frame);
		break;
	case DL_BYE:
		_dlReceivedByeFrame(frame);
		break;

	default:
		break;
	}
}

/* Utilities which aren't used when OS == 1 */
#if (CAL_USE_OS == 0)
/**
 * @brief	Funzione di scansione (estrazione) della coda contenente i messaggi di notifica
 * 			da inviare al livello superiore.
 * @retval	none.
 */
void _dlScanNotificationQueue()
{

	if (frameQueueLength(dlNotificationQueue) > 0)
	{
		DL_Frame *frame = dequeueFrame(dlNotificationQueue);

		if(frame->ifx<GET_MAX_INTERFACES())
		{
			//Get a copy of the Packet
			uint16_t packetLength = frame->data[DL_NUMCHUNKS_FIELD]* CHUNK_LENGTH - HEADER_LENGTH - frame->data[DL_PADDING_FIELD];
			uint8_t *packet = _dlGetPacketFromFrame(frame);


			CAL_InterfaceNumber ifx = frame->ifx;
			DL_Frame_Type type = frame->data[DL_FTYPE_FIELD];

			//Evaluates the frame type in order to call the right CAL Callback
			switch (type)
			{
				case DL_SENT_FAILED:
				{
					//Calls the CAL Send Error Callback
					calLogInt(CAL_LOG_ERROR,"_dlScanNotificationQueue","SENT-FAILED-IFX",(uint16_t)ifx);
					sendErrorCallback(ifx, packet,packetLength);
				}
				break;
				case DL_SENT:
				{
					calLogInt(CAL_LOG_INFORMATIONAL,"_dlScanNotificationQueue","FRAME-SENT-IFX",(uint16_t)ifx);
					sentPacketCallback(ifx, packet,packetLength);
				}
				break;

				default:{} break;
			}
			calLogInt(CAL_LOG_DEBUG,"_dlScanNotificationQueue","PACKET-FREED-B",(uint16_t)packetLength);
			calFree(packet);

			//In all cases frees resources (the upper layer MUST copy the packet).
			_dlFreeResources(frame->data[DL_SEQNUMBER_FIELD],0,0);
		}
		else
		{
			_dlFreeResources(-1,0,frame);
		}

	}
}

/**
 * @brief	Estrazione dalla coda della frame per inviare attraverso il PCLP.
 * @param	ifx: numero interfaccia.
 * @retval	none.
 */
void _dlExtractFrameToSend(CAL_InterfaceNumber ifx)
{

	DL_Frame *frame = 0;
	DL_NumChunks_Type numChunks = 0;
	frame = _dlPrepareToSendFrameOverInterface(ifx);

	if (frame != 0)
	{
		numChunks = frame->data[DL_NUMCHUNKS_FIELD];
		//Call the plcp in order to send the Frame in the interface IFx
		calLogInt(CAL_LOG_DEBUG,"_dlExtractFrameToSend","SENDING-FRAME-IFx",(uint16_t)ifx);
		plcpSendFrame(frame, numChunks);
	}
}

/**
 * @brief	Estrazione frame ricevute dalla coda.
 * @retval	none.
 */
void _dlExtractReceivedFrame() //Chiamata dal Timer
{

	if (frameQueueLength(dlRxQueue) == 0)
	return;

	DL_Frame *frame = dequeueFrame(dlRxQueue);

	_dlSwitchReceivedFrame(frame);
}

/**
 * @brief	Accodamento e tentativo di invio della frame
 * @param	frame: puntatore alla frame da inviare.
 * @param	ifx: numero interfaccia.
 * @retval	none.
 */
void _dlEnqueueAndTryToSend(DL_Frame *frame, CAL_InterfaceNumber ifx)
{
	calLogInt(CAL_LOG_DEBUG,"_dlEnqueueAndTryToSend","ENQUING-TX-FRAME-IFx",(uint16_t)ifx);
	//Enqueue the DL_Frame
	_dlEnqueueTxFrameQueue(ifx, frame);

	//If the interface IFx is ready sends now the frame.
	if (_dlGetInterfaceReadyStatus(ifx) == DL_READY)
	_dlExtractFrameToSend(ifx);
}

#endif

/**
 * @}
 */

/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

/**
 * @addtogroup CAL_DATALINK_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

/**
 * @brief	Inizializzazione del livello Datalink.
 * @param	none.

 * @retval	Esito inizializzazione, che pu� assumere uno dei seguenti valori:
 * 			@arg	DL_OK:	inizializzazione avvenuta con successo;
 * 			@arg	DL_ERROR:	errore qualsiasi durante l'inizializzazione, nessuna risorsa allocata.
 */
DL_Status dlInit()
{

	calLogInt(CAL_LOG_INFORMATIONAL,"dlInit","FUN-CALLED",0);
	memset(&dlInterfaceReady, DL_READY, GET_MAX_INTERFACES());
	memset(&seqNumberMap, AVAILABLE, DL_SEQ_NUMBER_MAP_SIZE);
	memset(&numRetryMap, 0, DL_SEQ_NUMBER_MAP_SIZE);
	memset(&tickMap, 0, DL_SEQ_NUMBER_MAP_SIZE);
	memset(&dlTempInterfaceStatus, CAL_NO, GET_MAX_INTERFACES());
	memset(&dlInterfaceAttachStatus, CAL_NO, GET_MAX_INTERFACES());


	//receivedPacketCounter = 0;
	seqNumberCounter = 0;
	lastUsedSeqNumber = 0;
	DL_Status status = DL_OK;

	//Initialize all dlQueues
	dlRxQueue = initFrameQueue();
	if (dlRxQueue == NULL)
		status = DL_ERROR;

	//If the status isn't OK doesn't initialize the Notification Queue
	if (status == DL_OK)
	{
		dlNotificationQueue = initFrameQueue();
		if (dlNotificationQueue == NULL)
		{
			deInitFrameQueue(dlRxQueue);
			status = DL_ERROR;
		}
	}

	int i = 0;
	while (i < GET_MAX_INTERFACES() && status == DL_OK)
	{
		dlTxQueue[i] = initFrameQueue();
		if (dlTxQueue[i] != NULL)
			++i;
		else
			status = DL_ERROR;
	}

	//If something is gone wrong perform a rollback
	if (status == DL_ERROR)
	{

		calLogInt(CAL_LOG_ERROR,"dlInit","INIT-ERROR",0);
		//In case of problems perform a deInit "rollback" operation
		int j = 0;
		while (j < i)
			deInitFrameQueue(dlTxQueue[j++]);

		deInitFrameQueue(dlRxQueue);
		deInitFrameQueue(dlNotificationQueue);
	}

#if (CAL_USE_OS == 0)
	timerScanCounter=0;
	CAL_TIM_Init(DL_TIMEOUT_PERIOD_MS);
	CAL_TIM_Start();
#endif
	//Enable CRC
	crcInit();
	return status;
}

/**
 * @brief	Invio di un pacchetto attraverso accodamento (Frame di tipo DATA).
 * @param	IFx: numero interfaccia da cui inviare la frame.
 * @param	packet: puntatore al pacchetto da inviare.
 * @param	packetLength: dimensione pacchetto in byte.
 * @param	numRetry: numero massimo di tentativi desiderati per inviare il pacchetto.
 * 			@arg numRetry = 0: nessun ritentativo di ritrasmissione (semantica best-effort);
 * 			@arg numRetry > 0: in caso di fallimenti saranno eseguiti al pi� numRetry tentativi di invio.
 *
 * @retval	none.
 */
void dlSendFrame(CAL_InterfaceNumber ifx, uint8_t* packet,
		uint16_t packetLength, uint8_t numRetry)
{


	calLogInt(CAL_LOG_INFORMATIONAL,"dlSendFrame","FUN-CALLED-IFx",ifx);
	// Log the dlSendFrame on IFx
	calLogInt(CAL_LOG_DEBUG, "dlSendFrame", "DL SEND FRAME CALLED ON IFx ", (uint16_t)ifx);
	calLogInt(CAL_LOG_DEBUG, "dlSendFrame", "DL SEND FRAME ON PACKET WITH LENGTH ", (uint16_t)packetLength);
	calLogInt(CAL_LOG_DEBUG, "dlSendFrame", "DL SEND FRAME ON PACKET WITH NUM RETRY ", (uint16_t)numRetry);

	DL_Status status = DL_ERROR;
	DL_Frame_Header *dlHeader = 0;
	DL_Frame *frame = 0;
	int16_t seqNumber = -1;
	//Check if the IFx is already enabled
	if (plcpGetInterfaceStatus(ifx) != CAL_NO)
	{
		seqNumber = _dlGetAvailableSeqNumber();
		if (seqNumber >= 0)
		{
			//Save the numRetry preferences for the frame which will be sent
			_dlSetNumRetry(seqNumber, numRetry);

			//Set the tick count
			_dlSetTick(seqNumber, DL_NUM_TICK_MAX);

			//Prepare the Header
			CAL_Option_Type calculateCRC = CAL_YES;
			if (crcCheckState() != 1)
				calculateCRC = CAL_NO;
			dlHeader = _dlPrepareHeader(DL_DATA, seqNumber, CAL_FIELD_RESERVED,
			HEADER_LENGTH, packetLength, CHUNK_LENGTH, calculateCRC);

			if (dlHeader != 0)
			{
				//Set Up the DL_Frame envelope ( IFx + Data area )
				frame = _dlPrepareFrame(ifx,
						dlHeader->numChunks * CHUNK_LENGTH);

				if (frame != 0 && frame->data != 0)
				{
					//Prepare the DL_Frame Data Payload (so put together Header + Payload + Padding)
					_dlPrepareFrameData(frame->data, dlHeader, HEADER_LENGTH,
							packet, packetLength, dlHeader->padding,
							calculateCRC);
					calLogInt(CAL_LOG_DEBUG, "dlSendFrame", "FRAME-PAYLOAD-ALLOCATED-B", (uint16_t)(dlHeader->numChunks * CHUNK_LENGTH));

					calFree(dlHeader);
					calLogInt(CAL_LOG_DEBUG, "dlSendFrame", "HEADER-FREED-B",(uint16_t)HEADER_LENGTH);

#if CAL_USE_OS == 0
					{
						status = DL_OK;
						_dlEnqueueAndTryToSend(frame, ifx);
					}
#else
					{
						if (_dlTaskEnqueueAndTryToSend(ifx, frame) != 0)
							status = DL_OK; //Frame inserted into TX Queue (All checks are passed!)
					}
#endif
				}

			}
		}

	}

	if (status == DL_ERROR)
	{
		calLogInt(CAL_LOG_INFORMATIONAL, "dlSendFrame", "SEND-ERROR-IFx", ifx);
		_dlFreeResources(seqNumber, dlHeader, frame);
		sendErrorCallback(ifx, packet,packetLength);
	}
}

/**
 * @brief	Abilitazione interfaccia ed invio frame di Welcome
 * @param	IFx: numero interfaccia da abilitare.
 * 			Può assumere i seguenti valori:
 * 			@arg IFx valore singolo: abilita interfaccia x;
 * 			@arg IF_ALL: abilita tutte le interfacce.
 *
 * @retval	none.
 */
void dlEnableInterface(CAL_InterfaceNumber ifx)
{

	// Log the dlEnableInterface on IFx
	calLogInt(CAL_LOG_DEBUG, "dlEnableInterface", "FUN-CALLED-IFx", (uint16_t)ifx);

	plcpEnableInterface(ifx);
	_dlSendWelcomeFrame(ifx);
}

/**
 * @brief	Disabilitazione interfaccia
 * @param	IFx: numero interfaccia da disabilitare.
 * 			Pu� assumere i seguenti valori:
 * 			@arg IFx valore singolo: disabilita interfaccia x;
 * 			@arg IF_ALL: disabilita tutte le interfacce.
 *
 * @retval	none.
 */
void dlDisableInterface(CAL_InterfaceNumber ifx)
{

	// Log the dlDisableInterface on IFx
	calLogInt(CAL_LOG_DEBUG, "dlDisableInterface", "FUN-CALLED-IFx", (uint16_t)ifx);

	//Prepare BYE Message for IFx
	_dlSendByeFrame(ifx);
}

/**
 * @brief	Restituisce una mappa con lo status delle interfacce per
 * 			capire quale di esse � stata abilitata.
 * @param	none.
 *
 * @retval	statusMap, puntatore ad un array CAL_Option_Type dove
 * 			statusMap[i] = CAL_YES o CAL_NO indica lo stato dell'interfaccia 'i'
 */
CAL_Option_Type* dlGetInterfaceStatusMap()
{
	calLogInt(CAL_LOG_DEBUG, "dlGetInterfaceStatusMap", "FUN-CALLED", 0);

	CAL_Option_Type *map = plcpGetInterfaceStatusMap();
	memcpy(dlTempInterfaceStatus, map, GET_MAX_INTERFACES());
	calFree(map);
	return dlTempInterfaceStatus;
}

/**
 * @brief	Restituisce l'attach status dell'interfaccia indicata come parametro.
 * @param	ifx	: interfaccia di cui conoscere l'interface Attach status.
 *
 * @retval	interfaceStatus dove
 * 			interfaceStatus = CAL_YES o CAL_NO indica lo stato di attach dell'interfaccia.
 */
CAL_Option_Type dlGetInterfaceAttachStatus(CAL_InterfaceNumber ifx)
{
	return dlInterfaceAttachStatus[ifx];
}
#if (CAL_USE_OS == 0)
/**
 * @brief	Callback di frame ricevuta (chiamata da PLCP)
 * @param	frame: puntatore alla frame ricevuta.
 * @retval	none.
 */
void dlReceivedFrame(DL_Frame *frame)
{
	// Log the dlReceivedFrame
	calLogInt(CAL_LOG_INFORMATIONAL, "dlReceivedFrame", "FUN-CALLED-IFx", (uint16_t)frame->ifx);
	enqueueFrame(dlRxQueue, frame);

}

// IF OS == 0
/**
 * @brief	Callback di avvenuto invio di una frame (chiamata da PLCP)
 * @param	IFx: numero interfaccia coinvolta sulla quale la frame � stata inviata.
 *
 * @retval	none.
 */
void dlFrameSentCallback(CAL_InterfaceNumber ifx)
{

	// Log the dlFrameSentCallback on IFx
	calLogInt(CAL_LOG_INFORMATIONAL, "dlFrameSentCallback", "FUN-CALLED-IFx", (uint16_t)ifx);

	//Performs the main operations when a frame is sent through ifx interface.
	_dlFrameSent(ifx);

	//Try to send another frame on the same IFx
	_dlExtractFrameToSend(ifx);
}

// IF OS == 0
/**
 * @brief	Error Callback sull'invio di una frame (chiamata da PLCP)
 * @param	IFx: numero interfaccia coinvolta nell'errore.
 *
 * @retval	none.
 */
void dlSendErrorCallback(CAL_InterfaceNumber ifx)
{

	// Log the sendErrorCallback on IFx
	calLogInt(CAL_LOG_WARNING, "dlSendErrorCallback", "FUN-CALLED-IFx", (uint16_t)ifx);

	//Get the frame and the SN related to IFx
	DL_Frame *frame = dlTxStagingArray[ifx];
	DL_SeqNumber_Type seqNumber = seqNumberMap[ifx];

	//Evaluate numRetry and if numRetry == 0 send and error to Upper layer by Notification Queue.
	_dlEvaluateNumRetry(frame, seqNumber);
}

// IF OS == 0

void dlTimerPeriodElapsedCallback()
{

	calLogInt(CAL_LOG_DEBUG, "dlTimerPeriodElapsedCallback", "FUN-CALLED", 0);
	//Software timer.
	timerScanCounter = (timerScanCounter+1)%2;
	_dlScanWaitingStagingArea();

	if(timerScanCounter == 0)
	{
		_dlExtractReceivedFrame();
		//TODO: Sviluppi futuri
//		if(receivedPacketCounter < 0)
//		{
//			uint8_t i=0;
//			CAL_Option_Type *map = plcpGetInterfaceStatusMap();
//			memcpy(dlTempInterfaceStatus, map, GET_MAX_INTERFACES());
//			calFree(map);
//			while (i < GET_MAX_INTERFACES())
//			{
//				if (dlTempInterfaceStatus[i] == CAL_YES)
//					dlDisableInterface(i);
//				i++;
//			}
//			i=0;
//			while (i < GET_MAX_INTERFACES())
//			{
//				if (dlTempInterfaceStatus[i] == CAL_YES)
//					dlEnableInterface(i);
//				i++;
//			}
//
//			receivedPacketCounter=0;
//		}
	}
	else
	_dlScanNotificationQueue();


}
#endif

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
