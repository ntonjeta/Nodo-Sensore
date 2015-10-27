/**
 ******************************************************************************
 * @file    plcp.c
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    28/giu/2015
 * @brief   TODO: brief for plcp.c
 ******************************************************************************
 */

/* Includes ********************************************************************/
#include "plcp.h"
#include "plcp_utils.h"
#include "utils/frame_utils.h"

/**
 * @addtogroup CAL_Module
 * @{
 */

/**
 * @addtogroup CAL_PHY Livello Fisico
 * @{
 */

/**
 * @addtogroup CAL_PHY_PLCP_Module Sottolivello PLCP
 * @{
 */

/* Private Constants ***********************************************************/
/* Private Macros **************************************************************/

/* Private Types ***************************************************************/

/**
 * @defgroup CAL_PHY_PLCP_Private_Types Private Types
 * @brief Tipi privati
 * @{
 */

PLCP_Interface* plcpInterfaces[GET_MAX_INTERFACES()];  /**< Array delle interfacce configurate */

/**
 * @}
 */

/* Private Functions ***********************************************************/

/**
 * @defgroup CAL_PHY_PLCP_Private_Functions Private Functions
 * @brief Funzioni private
 * @{
 */

/**
 * @brief	_storeTmpTxChunkOnIfx:	Memorizza il puntatore al chunk trasmesso al PMD in un'area temporanea
 * @param 	ifx:					Interfaccia su cui è stato trasmesso il chunk al PMD
 * @param 	chunk:					Puntatore al chunk trasmesso
 */
static void _storeTmpTxChunkOnIfx(CAL_InterfaceNumber ifx, PMD_Chunk* chunk)
{
	plcpInterfaces[ifx]->tmpTxChunk = chunk;
}

/**
 * @brief	_storeTmpRxChunkOnIfx:	Memorizza il puntatore al chunk predisposto per la ricezione al PMD in un'area temporanea
 * @param 	ifx:					Interfaccia su cui è stato predisposto il chunk per la ricezione al PMD
 * @param 	chunk:					Puntatore al chunk predisposto
 */
static void _storeTmpRxChunkOnIfx(CAL_InterfaceNumber ifx, PMD_Chunk* chunk)
{
	plcpInterfaces[ifx]->tmpRxChunk = chunk;
}

/**
 * @brief	_allocateAndReceiveNewChunk:	Alloca un nuovo predisposto per la ricezione e abilita la ricezione al livello PMD
 * @param	plcpIfx:						Interfaccia su cui allocare e abilitare la ricezione
 */
static void _allocateAndReceiveNewChunk(PLCP_Interface* plcpIfx)
{
	// Logging
	calLogInt(CAL_LOG_DEBUG, "_allocateAndReceiveNewChunk", "IFx-CHUNK-RECEIVE", plcpIfx->ifxNumber);

	// Enable the receipt of the first chunk
	PMD_Chunk* newChunk = _allocateChunk();
	newChunk->pmdIfx = plcpIfx->pmdIfx;

	// Store the pointer to this temp chunk
	_storeTmpRxChunkOnIfx(plcpIfx->ifxNumber, newChunk);

	// Receive
	pmdReceive(newChunk);
}

/**
 * @brief	_plcpPmdInit:	Abilita l'interfaccia specificata, alloca e invia un nuovo chunk predisposto per la ricezione al livello PMD
 * @param	plcpIfx:		Puntatore all'interfaccia da abilitare
 * @return	PMD_Status:		Esito dell'operazione di abilitazione
 */
static PMD_Status _plcpPmdInit(PLCP_Interface* plcpIfx)
{
	// Init the desired pmd interface
	PMD_Status status = pmdInit(plcpIfx->pmdIfx);
	if (status == PMD_OK)
	{
		// Receive a new chunk
		_allocateAndReceiveNewChunk(plcpIfx);

		return PMD_OK;
	}
	return status;
}

/**
 * @brief	_plcpPmdDeInit:	Disabilita l'interfaccia specificata e svuota le code in trasmissione e ricezione di quell'interfaccia
 * @param 	plcpIfx:		Interfaccia da disabilitare
 * @return	PMD_Status:		Esito dell'operazione di disabilitazione
 */
static PMD_Status _plcpPmdDeInit(PLCP_Interface* plcpIfx)
{
	// DeInit the desidered pmd interface
	PMD_Status status = pmdDeInit(plcpIfx->pmdIfx);
	if (status == PMD_OK)
	{
		// Clean buffers before the deinitialization
		_cleanChunksOnQueue(plcpIfx->rxQueue);
		_cleanChunksOnQueue(plcpIfx->txQueue);

		// Return OK!
		return PMD_OK;
	}
	return status;
}

#if (CAL_USE_OS == 0)

/**
 * @brief	_sendNextEnqueuedChunk:	Questa funzione privata (compilata se non c'è il supporto all'OS) è utilizzata
 * 									per inviare il prossimo chunk al PMD da trasmettere
 * @param	queue:					La coda da cui schedulare il prossimo chunk
 */
static void _sendNextEnqueuedChunk(PLCP_ChunkQueue* queue)
{
	// have a pointer to the nextChunk to be extracted
	PMD_Chunk* nextChunk = _getNextEnqueuedChunkOnQueue(queue);

	// send through the pmd level
	pmdSend(nextChunk);
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
 * @addtogroup CAL_PHY_PLCP_UTILS_Exported_Functions Utility Exported Functions
 * @{
 */

/**
 * @brief	_getNextEnqueuedChunkOnIfx: Estrae il chunk successivo da trasmettere dalla coda dell'interfaccia specificata
 * @param 	ifx:						Interfaccia da cui estrarre il chunk successivo da trasmettere
 * @return	PMD_Chunk*:					Puntatore al chunk da trasmettere
 */
PMD_Chunk* _getNextEnqueuedChunkOnIfx(CAL_InterfaceNumber ifx)
{
	return _getNextEnqueuedChunkOnQueue(plcpInterfaces[ifx]->txQueue);
}

/**
 * @brief	_getNextEnqueuedChunkOnQueue:	Estrae il chunk successivo da trasmettere dalla coda specificata
 * @param 	queue:							Coda da cui estrarre il chunk successivo da trasmettere
 * @return	PMD_Chunk*:						Puntatore al chunk da trasmettere
 */
PMD_Chunk* _getNextEnqueuedChunkOnQueue(PLCP_ChunkQueue* queue)
{
	if (chunkQueueLength(queue) == 0)
	{
		// Nothing to send
		return NULL;
	}

	// Get the nextChunk
	PMD_Chunk* nextChunk = dequeueChunk(queue);

	// Store the tmp chunk
	_storeTmpTxChunkOnIfx(nextChunk->pmdIfx->ifxNumber, nextChunk);

	// Return a pointer to the next chunk received
	return nextChunk;
}

/**
 * @brief	_allocateChunk:	Alloca un nuovo chunk generico
 * @return	PMD_Chunk*:		Puntatore al nuovo chunk allocato
 */
PMD_Chunk* _allocateChunk()
{
	PMD_Chunk* chunk = calMalloc( sizeof(PMD_Chunk) );
	chunk->data = calMalloc( CHUNK_LENGTH * sizeof(uint8_t) );
	chunk->isLastChunk = CAL_NO;

	// Logging
	calLogInt(CAL_LOG_DEBUG, "_allocateChunk", "CHUNK-ALLOCATED-B", sizeof( PMD_Chunk ) + CHUNK_LENGTH * sizeof( uint8_t ) );

	return chunk;
}

/**
 * @brief	_deAllocateChunk:	Dealloca un chunk generico
 * @param 	PMD_Chunk*:			Puntatore al chunk da deallocare
 */
void _deAllocateChunk(PMD_Chunk* chunk)
{
	calFree(chunk->data);
	calFree(chunk);

	// Logging
	calLogInt(CAL_LOG_DEBUG, "_deAllocateChunk", "CHUNK-DEALLOCATED-B", sizeof( PMD_Chunk ) + CHUNK_LENGTH * sizeof( uint8_t ) );
}

/**
 * @brief	_cleanReceivedChunksOnIfx:	Svuota la coda in ricezione (deallocando automaticamente i chunk contenuti) sull'interfaccia specificata come parametro
 * @param	ifx:						Interfaccia su cui svuotare la coda dei chunk in ricezione
 */
void _cleanReceivedChunksOnIfx(CAL_InterfaceNumber ifx)
{
	_cleanChunksOnQueue(plcpInterfaces[ifx]->rxQueue);
}

/**
 * @brief	_cleanSendChunksOnIfx:	Svuota la coda in trasmissione (deallocando automaticamente i chunk contenuti) sull'interfaccia specificata come parametro
 * @param	ifx:					Interfaccia su cui svuotare la coda dei chunk in trasmissione
 */
void _cleanSendChunksOnIfx(CAL_InterfaceNumber ifx)
{
	_cleanChunksOnQueue(plcpInterfaces[ifx]->txQueue);
}

/**
 * @brief	_cleanChunksOnQueue:	Svuota tutti i chunk contenuti nella coda specificata come parametro
 * @param 	queue:					Coda da svuotare
 */
void _cleanChunksOnQueue(PLCP_ChunkQueue* queue)
{
	// Logging
	calLogInt(CAL_LOG_DEBUG, "_cleanChunksOnQueue", "CHUNKS-QUEUE-CLEANING", 0);

	while(chunkQueueLength(queue) > 0)
	{
		// Extract the chunk from the queue
		PMD_Chunk* tmpChunk = dequeueChunk(queue);

		// Deallocate it
		_deAllocateChunk(tmpChunk);
	}
}

/**
 * @brief	_allocateReceiveChunkForIfx:	Alloca un nuovo chunk predisposto alla ricezione, ma non lo trasmette al PMD
 * 											(questa funzione è utilizzata dai task nel caso in cui CAL_USE_OS = 1)
 * @param	ifx:							Interfaccia su cui predisporre un nuovo chunk in ricezione
 * @return	PMD_Chunk*:						Puntatore al chunk allocato
 */
PMD_Chunk* _allocateReceiveChunkForIfx(CAL_InterfaceNumber ifx)
{
	// Allocate
	PMD_Chunk* chunk = _allocateChunk();
	chunk->pmdIfx = plcpInterfaces[ifx]->pmdIfx;

	// Store the pointer to this temp chunk
	_storeTmpRxChunkOnIfx(ifx, chunk);

	// Return
	return chunk;
}

/**
 * @brief	_getEnableStatusOnIfx:	Restituisce lo stato di abilitazione dell'interfaccia specificata come parametro
 * @param	ifx:					Interfaccia da cui ottenere lo stato
 * @return	CAL_Option_Type:		Stato di abilitazione (CAL_YES o CAL_NO)
 */
CAL_Option_Type _getEnableStatusOnIfx(CAL_InterfaceNumber ifx)
{
	return plcpInterfaces[ifx]->enabled;
}

/**
 * @brief	_enqueueFrameChunks:	Questa funzione scompone la frame in chunks e li accoda nella coda in trasmissione
 * @param 	frame:					Puntatore alla DL_Frame composta dal DATALINK
 * @param 	numChunks:				Numero di chunk in cui scomporre la frame
 */
void _enqueueFrameChunks(DL_Frame* frame, DL_NumChunks_Type numChunks)
{
	// extract the specified interface
	PLCP_Interface* plcpIfx = plcpInterfaces[frame->ifx];

	// The frame data length MUST be a multiple of CHUNK_LENGTH
	// The padding is managed by the datalink layer
	uint8_t* tmpPtr = frame->data;

	// This for will break up the frame->data into numChunks chunks
	for (uint8_t i = 0; i < numChunks; i++)
	{
		// make a tmp pointer to a new allocated chunk
		PMD_Chunk* currentChunk = _allocateChunk();

		// assign the interface to the chunk
		currentChunk->pmdIfx = plcpIfx->pmdIfx;

		// copy the chunk
		memcpy(currentChunk->data, tmpPtr, CHUNK_LENGTH);

		// increment the pointer of CHUNK_LENGTH bytes
		tmpPtr += CHUNK_LENGTH;

		// if this is the last chunk, flag it
		if (i == (numChunks - 1))
		{
			currentChunk->isLastChunk = CAL_YES;
		}

		// enqueue the current chunk
		enqueueChunk(plcpIfx->txQueue, currentChunk);
	}

	calLogInt(CAL_LOG_DEBUG, "_enqueueFrameChunks", "CHUNKS-ENQUEUED", (uint16_t)numChunks);
}

/**
 * @brief	_enqueueReceivedChunk:	Accoda il chunk passato come parametro nella coda in ricezione dei chunk
 * @param	chunk:					Puntatore al chunk da accodare
 */
void _enqueueReceivedChunk(PMD_Chunk* chunk)
{
	// Enqueue the received chunk
	enqueueChunk(plcpInterfaces[chunk->pmdIfx->ifxNumber]->rxQueue, chunk);
}

/**
 * @brief	_buildReceivedFrameOnIfx:	Questa funzione tenta di costruire una frame completa sull'interfaccia specificata come parametro di ingresso.
 * 										L'esito dell'operazione dipende dal numero dei chunk ricevuti, ovvero se questi sono sufficienti a costruire una frame completa
 * @param	ifx:						Interfaccia su cui costruire una frame in ricezione
 * @return	DL_Frame*					Puntatore alla frame ricevuta
 */
DL_Frame* _buildReceivedFrameOnIfx(CAL_InterfaceNumber ifx)
{
	return _buildReceivedFrameOnQueue(plcpInterfaces[ifx]->rxQueue);
}

/**
 * @brief	_buildReceivedFrameOnQueue:	Questa funzione tenta di costruire una frame completa a partire dalla coda dei chunk specificata in ingresso.
 * 										L'esito dell'operazione dipende dal numero dei chunk ricevuti, ovvero se questi sono sufficienti a costruire una frame completa.
 * @param	queue:						La coda da cui estrarre i chunk per la composizione di una frame completa
 * @return	DL_Frame*					Puntatore alla frame ricevuta
 */
DL_Frame* _buildReceivedFrameOnQueue(PLCP_ChunkQueue* queue)
{
	// Here we have to check if all frame's chunks are arrived
	PMD_Chunk* headerChunk = queueGetHeadChunk(queue);

	// Read numChunksRequired to complete the frame on this interface
	uint8_t numChunksRequired = dlGetFieldValue(headerChunk->data, DL_NUMCHUNKS_FIELD);

	// Do we have all the chunks?
	if (chunkQueueLength(queue) >= numChunksRequired)
	{
		// Now build the frame by merging all the chunks
		DL_Frame* frame = calMalloc( sizeof( DL_Frame ) );
		frame->data = calMalloc( CHUNK_LENGTH * numChunksRequired * sizeof(uint8_t) );

		calLogInt(CAL_LOG_DEBUG, "_buildReceivedFrameOnQueue", "DLFRAME-ALLOCATED-B", sizeof( DL_Frame ) + (CHUNK_LENGTH * numChunksRequired * sizeof(uint8_t)));

		// Set a pointer to frame->data used to merge everything
		uint8_t* tmpPtr = frame->data;
		for (uint8_t i = 0; i < numChunksRequired; i++)
		{
			// Extract the chunk from the queue
			PMD_Chunk* chunk = dequeueChunk(queue);

			// Copy to the area pointed by the tmpPtr
			memcpy(tmpPtr, chunk->data, CHUNK_LENGTH);

			// Increment the tpmPtr
			tmpPtr += CHUNK_LENGTH;

			// Now we are ready to deallocate the previously allocated chunk
			_deAllocateChunk(chunk);
		}

		// Return the frame
		return frame;
	}
	else
	{
		// Into the queue there aren't enough chunk to build the frame
		return NULL;
	}
}

/**
 * @brief	_getReceiveStatusOnIfx:	Ritorna lo stato della FSM per il processo di ricezione sull'interfaccia specificata come parametro di ingresso
 * @param 	ifx:					Interfaccia da cui estrarre lo stato del processo FSM in ricezione
 * @return	PLCP_ReceiveStatus:		Stato della FSM
 */
PLCP_ReceiveStatus _getReceiveStatusOnIfx(CAL_InterfaceNumber ifx)
{
	return _getReceiveStatusOnPlcpIfx(plcpInterfaces[ifx]);
}

/**
 * @brief	_getReceiveStatusOnPlcpIfx:	Ritorna lo stato della FSM per il processo di ricezione sull'interfaccia specificata come parametro di ingresso
 * @param 	plcpIfx:					Interfaccia PLCP da cui estrarre lo stato del processo FSM in ricezione
 * @return	PLCP_ReceiveStatus:			Stato della FSM
 */
PLCP_ReceiveStatus _getReceiveStatusOnPlcpIfx(PLCP_Interface* plcpIfx)
{
	return plcpIfx->rxStatus;
}

/**
 * @brief	_setReceiveStatusOnIfx:	Setta lo stato della FSM per il processo di ricezione sull'interfaccia specificata come parametro di ingresso
 * @param 	ifx:					Interfaccia su cui settare lo stato del processo FSM in ricezione
 * @param	rxStatus:				Stato da settare
 */
void _setReceiveStatusOnIfx(CAL_InterfaceNumber ifx, PLCP_ReceiveStatus rxStatus)
{
	_setReceiveStatusOnPlcpIfx(plcpInterfaces[ifx], rxStatus);
}

/**
 * @brief	_setReceiveStatusOnIfx:	Setta lo stato della FSM per il processo di ricezione sull'interfaccia specificata come parametro di ingresso
 * @param 	plcpIfx:				Interfaccia PLCP su cui settare lo stato del processo FSM in ricezione
 * @param	rxStatus:				Stato da settare
 */
void _setReceiveStatusOnPlcpIfx(PLCP_Interface* plcpIfx, PLCP_ReceiveStatus rxStatus)
{
	plcpIfx->rxStatus = rxStatus;
}

/**
 * @}
 */

/**
 * @addtogroup CAL_PLCP_Exported_Functions Exported Functions
 * @brief Funzioni esportate
 * @{
 */

/**
 * @brief	plcpInit:	Attiva la configurazione del PLCP
 */
void plcpInit()
{
	// Logging
	calLogInt(CAL_LOG_DEBUG, "plcpInit", "FUN-CALLED", 0);

	// Simply call the plcpConfigPmdInterfaces function to configure all the internal PLCP and PMD interfaces
	plcpConfigPmdInterfaces();
}

/**
 * @brief 	plcpConfigPmdInterfaces:	Configurazione delle interfacce di comunicazione e configurazione dello strato PMD.
 * 										Questa funzione dovrà essere chiamata una sola volta all'avvio.
 */
void plcpConfigPmdInterfaces()
{
	CAL_InterfaceNumber calIfxNumber = 0; // IF0

	for (uint8_t j = 0; j < IFX_TYPES_COUNT; j++)
	{
		// estraggo dalla configurazione il tipo di interfaccia da configurare
		PMD_InterfaceTypeConfig typeConfig = interfacesConfig[j];

		// quante interfacce di questo tipo devo configurare? (impostazione data da chi scrive il port in typeConfig.count)
		for (uint8_t i = 1; i <= typeConfig.count; i++)
		{
			// Init the PLCP interface wrapper
			PLCP_Interface* plcpIfx = calMalloc( sizeof( PLCP_Interface ) );

			// Logging
			calLogInt(CAL_LOG_DEBUG, "plcpConfigPmdInterfaces", "PLCP_IFX-ALLOCATED-B", sizeof( PLCP_Interface ) );

			// Allocate the inner interface (for the pmd level)
			plcpIfx->pmdIfx = calMalloc( sizeof( PMD_Interface ) );

			// Logging
			calLogInt(CAL_LOG_DEBUG, "plcpConfigPmdInterfaces", "PMD_IFX-ALLOCATED-B", sizeof( PMD_Interface ) );

			// Set all properties of the inner interface (for the pmd level)
			plcpIfx->pmdIfx->type = typeConfig.type;
			plcpIfx->pmdIfx->id = i;
			plcpIfx->pmdIfx->ifxNumber = calIfxNumber; // this is needed when the chunk came back from the pmd level
			plcpIfx->pmdIfx->status = PMD_IF_STATUS_NOT_CONFIGURED;

			// Configure the pmd with the provided inner interface
			pmdConfig(plcpIfx->pmdIfx);

			// Set the interface number
			plcpIfx->ifxNumber = calIfxNumber;

			// Init the chunk queues
			plcpIfx->txQueue = initChunkQueue();
			plcpIfx->rxQueue = initChunkQueue();

			// Set the enable status to NO
			plcpIfx->enabled = CAL_NO;

			// store the interfaceWrapper
			plcpInterfaces[calIfxNumber++] = plcpIfx;

			// Info
			calLogInt(CAL_LOG_INFORMATIONAL, "plcpConfigPmdInterfaces", "PLCP_IFX-CONFIGURED", (uint16_t)plcpIfx->ifxNumber);
		}
	}
}

/**
 * @brief	plcpEnableInterface:	Abilita l'interfaccia di comunicazione ifx in modalità atomica.
 * @param 	ifx:					Interfaccia da abilitare
 * @retval CAL_Status
 */
CAL_Status plcpEnableInterface(CAL_InterfaceNumber ifx)
{
	if (ifx != IF_ALL)
	{
		// If only one ifx is required to enable, do not manage the atomicity
		PMD_Status status = _plcpPmdInit(plcpInterfaces[ifx]);
		if (status == PMD_ALREADY_INITIALIZED || status == PMD_OK)
		{
			// Set the interface enabled
			plcpInterfaces[ifx]->enabled = CAL_YES;

			// (Re)Set the rxStatus to header expected
			_setReceiveStatusOnIfx(ifx, PLCP_RX_HEADER_EXPECTED);

			// Log the number of IFX enabled
			calLogInt(CAL_LOG_INFORMATIONAL, "plcpEnableInterface", "IFx-ENABLED", (uint16_t)ifx);

			return CAL_OK;
		}
		else
		{
			// Set the interface disabled
			plcpInterfaces[ifx]->enabled = CAL_NO;

			// Log the error on the pmdInit
			calLogInt(CAL_LOG_ERROR, "plcpEnableInterface", "IFx-ENABLE-ERROR", (uint16_t)ifx);

			return CAL_ERROR;
		}
	}
	else
	{
		// Otherwise the enable is atomic.
		// If one initialization fails, all the previous initialization will be rolled-back by the deInit
		uint8_t failed = 0;
		uint8_t i = 0;
		while ( i < GET_MAX_INTERFACES() && failed == 0)
		{
			PMD_Status status = _plcpPmdInit(plcpInterfaces[i]);
			if (status != PMD_ALREADY_INITIALIZED && status != PMD_OK)
			{
				// Some error occur on the initialization
				// This will cause to exit the while at the next cycle
				failed = 1;

				calLogString(CAL_LOG_ERROR, "plcpEnableInterface", "IFx-ENABLE-ERROR", "Attempt to enable all interfaces failed");
			}
			else
			{
				// If CAL_OK, just increment i and keep going on the next interface...
				plcpInterfaces[i]->enabled = CAL_YES;

				// Log the number of IFX attached
				calLogInt(CAL_LOG_INFORMATIONAL, "plcpEnableInterface", "IFx-ENABLED", (uint16_t)i);

				// (Re)Set the rxStatus to header expected
				_setReceiveStatusOnIfx(i, PLCP_RX_HEADER_EXPECTED);
				i++;
			}
		}

		// If we exited for errors, perform the rollback
		if (failed == 1 && i > 0)
		{
			for (uint8_t j = 0; j < i; j++)
			{
				_plcpPmdDeInit(plcpInterfaces[j]);
				plcpInterfaces[j]->enabled = CAL_NO;
			}
			return CAL_ERROR;
		}

		return CAL_OK;
	}
}

/**
 * @brief	plcpDisableInterface:	Disabilita l'interfaccia di comunicazione ifx
 * @param 	ifx:					Interfaccia da disabilitare
 * @retval CAL_Status
 */
CAL_Status plcpDisableInterface(CAL_InterfaceNumber ifx)
{
	if (ifx != IF_ALL)
	{
		// Disable the specific interface
		PMD_Status status = _plcpPmdDeInit(plcpInterfaces[ifx]);
		if (status == PMD_OK)
		{
			// Set to disabled
			plcpInterfaces[ifx]->enabled = CAL_NO;

			// DeAllocate the temporary chunks for current TX and RX
			_deAllocateChunk(plcpInterfaces[ifx]->tmpRxChunk);
			_deAllocateChunk(plcpInterfaces[ifx]->tmpTxChunk);

			// Log the number of IFX disabled
			calLogInt(CAL_LOG_INFORMATIONAL, "plcpEnableInterface", "IFx-DISABLED", (uint16_t)ifx);

			return CAL_OK;
		}
		else
		{
			// Log the number of IFX not disabled
			calLogInt(CAL_LOG_INFORMATIONAL, "plcpEnableInterface", "IFx-DISABLE-ERROR", (uint16_t)ifx);
			plcpInterfaces[ifx]->enabled = CAL_YES;
			return CAL_ERROR;
		}
	}
	else
	{
		// Disable all interfaces
		for (int i = 0; i < GET_MAX_INTERFACES(); i++)
		{
			// DeInit
			_plcpPmdDeInit(plcpInterfaces[i]);

			// Set to disabled
			plcpInterfaces[ifx]->enabled = CAL_NO;

			// DeAllocate the temporary chunks for current TX and RX
			_deAllocateChunk(plcpInterfaces[ifx]->tmpRxChunk);
			_deAllocateChunk(plcpInterfaces[ifx]->tmpTxChunk);
		}

		// Logging
		calLogString(CAL_LOG_INFORMATIONAL, "plcpEnableInterface", "IFx-DISABLED", "All interfaces disabled");

		return CAL_OK;
	}
}

/**
 * @brief		plcpGetInterfaceStatus:	Ritorna un CAL_Option_Type con lo stato dell'interfaccia
 * @param 		ifx:					Interfaccia ifx di cui ottenere lo stato di abilitazione
 * @return		CAL_Option_Type			CAL_YES se l'interfaccia è abilitata, CAL_NO se è disabilitata
 */
CAL_Option_Type plcpGetInterfaceStatus(CAL_InterfaceNumber ifx)
{
	return plcpInterfaces[ifx]->enabled;
}

/**
 * @brief	plcpGetInterfaceStatusMap:	Questa funzione restituisce al livello DATALINK un array di CAL_Option_Type,
 * 										indicizzato utilizzando l'ifx, che indica quale interfaccia è abilitata o meno.
 * @return	CAL_Option_Type*:			Puntatore all'array che contiene una lista delle interfacce attive
 */
CAL_Option_Type* plcpGetInterfaceStatusMap()
{
	// Logging
	calLogInt(CAL_LOG_DEBUG, "plcpGetInterfaceStatusMap", "FUN-CALLED", 0);

	// Allocate the map of statuses
	CAL_Option_Type* map = calMalloc( GET_MAX_INTERFACES()*sizeof(CAL_Option_Type) );
	for (uint8_t i = 0; i < GET_MAX_INTERFACES(); i++)
	{
		map[i] = plcpInterfaces[i]->enabled;
	}
	return map;
}

#if (CAL_USE_OS == 0)

/**
 * @brief	plcpSendFrame:	Questa funzione ha il compito di inviare una frame (proveniente dal livello DATALINK)
 * 							sull'interfaccia specificata nel primo parametro di ingresso
 *
 * @param 	frame:			La frame allocata e composta dal livello DATALINK
 * @param 	numChunks:		Il numero di chunk che compongono la frame
 */
void plcpSendFrame(DL_Frame* frame, DL_NumChunks_Type numChunks)
{
	// Logging
	calLogInt(CAL_LOG_DEBUG, "plcpSendFrame", "FUN-CALLED", 0);

	if (_getEnableStatusOnIfx(frame->ifx) == CAL_NO)
	{
		// Can't send a frame on a disabled interface
		calLogInt(CAL_LOG_ERROR, "plcpSendFrame", "FUN-CALLED", 0);
		return;
	}

	// Breakup the frame in chunks and enqueue them
	_enqueueFrameChunks(frame, numChunks);

	// Send the first chunk for this frame
	_sendNextEnqueuedChunk(plcpInterfaces[frame->ifx]->txQueue);
}

/**
 * @defgroup CAL_PHY_PLCP_Exported_Callback Exported Callback
 * @brief Callback richiamate dai livelli inferiori
 * @{
 */

/**
 * @brief	plcpChunkReceivedCallback:	Callback invocata dal livello PMD quando è stato ricevuto un nuovo chunk
 * @param 	chunk:						Chunk ricevuto
 */
void plcpChunkReceivedCallback(PMD_Chunk* chunk)
{
	// Logging
	calLogInt(CAL_LOG_DEBUG, "plcpChunkReceivedCallback", "FUN-CALLED", 0);

	extern void dlReceivedFrame(DL_Frame*);

	// Get the interface number
	PLCP_Interface* plcpIfx = plcpInterfaces[chunk->pmdIfx->ifxNumber];

	// Get the status of the interface
	PLCP_ReceiveStatus plcpRxStatus = _getReceiveStatusOnPlcpIfx(plcpIfx);

	if (plcpRxStatus == PLCP_RX_HEADER_EXPECTED)
	{
		// An header is expected, so check if this chunk is an header
		if (isHeader(chunk->data) == CAL_YES)
		{
			// Logging
			calLogString(CAL_LOG_DEBUG, "plcpChunkReceivedCallback", "CHUNK-RECEIVED", "Header chunk received when an header chunk was expected");

			// Enqueue the received chunk (header)
			enqueueChunk(plcpIfx->rxQueue, chunk);

			// We should try to build the frame, because there should be also frame with length 1 chunk (only header)
			DL_Frame* frame = _buildReceivedFrameOnQueue(plcpIfx->rxQueue);

			// If the _buildReceivedFrameOnQueue has built the frame correctly (all frame's chunks have been received)
			if (frame != NULL)
			{
				calLogString(CAL_LOG_INFORMATIONAL, "plcpChunkReceivedCallback", "FRAME-RECEIVED", "All chunks have been assembled into a frame");

				// Set the interface to the DL_Frame
				frame->ifx = plcpIfx->ifxNumber;

				// We don't need to change the receive status because we still expect an header now

				// Notify and pass to the DATALINK the new received frame
				dlReceivedFrame(frame);
			}
			else
			{
				// This chunk is an header, so change the FSM status
				_setReceiveStatusOnPlcpIfx(plcpIfx, PLCP_RX_DATA_EXPECTED);
			}
		}
		else
		{
			// Logging
			calLogString(CAL_LOG_WARNING, "plcpChunkReceivedCallback", "CHUNK-RECEIVED", "Data chunk received when an header chunk was expected");

			// The chunk is not an header, but an header was expected... so reject it.
			_deAllocateChunk(chunk);

			// Wait for a new header, so we don't change the FSM status
		}
	}
	else if (plcpRxStatus == PLCP_RX_DATA_EXPECTED)
	{
		// Check if the arrived chunk is a normal data chunk
		if (isHeader(chunk->data) == CAL_NO)
		{
			// Logging
			calLogString(CAL_LOG_DEBUG, "plcpChunkReceivedCallback", "CHUNK-RECEIVED", "Data chunk received when a data chunk was expected");

			// Ok, the received chunk isn't an header, so try to build the frame

			// Enqueue the received chunk
			enqueueChunk(plcpIfx->rxQueue, chunk);

			// Try to build the frame
			DL_Frame* frame = _buildReceivedFrameOnQueue(plcpIfx->rxQueue);

			// If the _buildReceivedFrameOnQueue has built the frame correctly (all frame's chunks have been received)
			if (frame != NULL)
			{
				calLogString(CAL_LOG_INFORMATIONAL, "plcpChunkReceivedCallback", "FRAME-RECEIVED", "All chunks have been assembled into a frame");

				// Set the interface to the DL_Frame
				frame->ifx = plcpIfx->ifxNumber;

				// Change the status of the receive process (because we now expect an header)
				_setReceiveStatusOnPlcpIfx(plcpIfx, PLCP_RX_HEADER_EXPECTED);

				// Notify and pass to the DATALINK the new received frame
				dlReceivedFrame(frame);
			}
		}
		else
		{
			// We have received a new header when it was not expected
			// Clean the queue for the previous received chunks (all discarded and rejected)

			// Logging
			calLogString(CAL_LOG_WARNING, "plcpChunkReceivedCallback", "CHUNK-RECEIVED", "Header chunk received when a data chunk was expected");

			_cleanChunksOnQueue(plcpIfx->rxQueue);

			// Enqueue the received chunk (header)
			enqueueChunk(plcpIfx->rxQueue, chunk);

			// Don't change the rx FSM status, because we now still expect data chunks
		}
	}

	// Receive a new chunk from the PMD
	_allocateAndReceiveNewChunk(plcpIfx);
}

/**
 * @brief	plcpChunkSentCallback:	Callback invocata dal livello PMD quando è terminata la trasmissione di un chunk
 * @param 	chunk:					Chunk inviato
 */
void plcpChunkSentCallback(PMD_Chunk* chunk)
{
	// Logging
	calLogInt(CAL_LOG_DEBUG, "plcpChunkSentCallback", "FUN-CALLED", 0);

	extern void dlFrameSentCallback(CAL_InterfaceNumber);

	// Extract the required plcpIfx
	PLCP_Interface* plcpIfx = plcpInterfaces[chunk->pmdIfx->ifxNumber];

	// the pmd level has sent a chunk. Is it the last chunk?
	if (chunk->isLastChunk == CAL_YES)
	{
		// Logging
		calLogString(CAL_LOG_DEBUG, "plcpChunkSentCallback", "CHUNK-SENT", "Last chunk sent");

		// Now deallocate the chunk
		_deAllocateChunk(chunk);

		// Logging
		calLogString(CAL_LOG_INFORMATIONAL, "plcpChunkSentCallback", "FRAME-SENT", "All chunks have been sent");

		// Notify the datalink layer that a frame is arrived on the specified interface
		dlFrameSentCallback(plcpIfx->ifxNumber);
	}
	else
	{
		// Logging
		calLogString(CAL_LOG_DEBUG, "plcpChunkSentCallback", "CHUNK-SENT", "Chunk sent. Sending the next chunk");

		// Now deallocate the chunk
		_deAllocateChunk(chunk);

		// Send another chunk on this interface
		_sendNextEnqueuedChunk(plcpIfx->txQueue);
	}
}

void plcpChunkSendErrorCallback(PMD_Chunk* chunk)
{
	// Logging
	calLogInt(CAL_LOG_WARNING, "plcpChunkSendErrorCallback", "FUN-CALLED", 0);

	extern void dlSendErrorCallback(CAL_InterfaceNumber);

	PLCP_Interface* plcpIfx = plcpInterfaces[chunk->pmdIfx->ifxNumber];

	// Dequeue and deallocate all remaining chunks to be sent into the txQueue
	_cleanChunksOnQueue(plcpIfx->txQueue);

	// Deallocate the last chunk with error
	_deAllocateChunk(chunk);

	// Notify the DATALINK about the error on the transmission
	dlSendErrorCallback(chunk->pmdIfx->ifxNumber);
}

void plcpChunkReceiveErrorCallback(PMD_Chunk* chunk)
{
	// Logging
	calLogInt(CAL_LOG_WARNING, "plcpChunkReceiveErrorCallback", "FUN-CALLED", 0);

	PLCP_Interface* plcpIfx = plcpInterfaces[chunk->pmdIfx->ifxNumber];

	// Dequeue and deallocate all chunks already received into the rxQueue
	_cleanChunksOnQueue(plcpIfx->rxQueue);

	// Deallocate this chunk
	_deAllocateChunk(chunk);

	// (Re)Set the rxStatus to header expected
	_setReceiveStatusOnPlcpIfx(plcpIfx, PLCP_RX_HEADER_EXPECTED);

	// Start the receipt of a new chunk (that is supposed to be the chunk containing the HEADER of a new frame, with no errors)
	_allocateAndReceiveNewChunk(plcpIfx);
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */


#endif
