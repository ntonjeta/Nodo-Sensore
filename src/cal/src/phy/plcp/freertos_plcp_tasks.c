/**
 ******************************************************************************
 * @file    plcp.c
 * @author  SE4 Sistemi Embedded Team (Di Fiore Giovanni, Iannucci Federico, Miranda Salvatore)
 * @version V1.0
 * @date    02/lug/2015
 * @brief   TODO: brief for plcp.c
 ******************************************************************************
 */

/* Includes ********************************************************************/
#include "plcp.h"

/**
 * @addtogroup CAL_Module
 * @{
 */

#if (CAL_USE_OS == 1)
#include "plcp_utils.h"
#include "freertos_tasks.h"
#include "utils/frame_utils.h"

/* Private Constants ***********************************************************/
/* Private Macros **************************************************************/
/* Private Types ***************************************************************/
/* Private Variables ***********************************************************/
/* Private Functions ***********************************************************/
/* Exported Constants **********************************************************/
/* Exported Macros *************************************************************/
/* Exported Types **************************************************************/
/* Exported Variables **********************************************************/
/* Exported Functions **********************************************************/

void vPlcpDownstreamTask(void* pvParameters)
{
	// The input parameter of the task is not used
	calUnused(pvParameters);

	// This task manages the messages received from the DATALINK level
	vPlcpDownstreamQueue_handle = xQueueCreate(IFX_TYPES_COUNT*2,
			sizeof(FREERTOS_CAL_Message));

	// Declare two messages
	FREERTOS_CAL_Message rxMessage;
	FREERTOS_CAL_Message txMessage;

	for (;;)
	{
		if (xQueueReceive(vPlcpDownstreamQueue_handle, &rxMessage,
				portMAX_DELAY))
		{
			// If a new message is received
			switch (rxMessage.type)
			{
			case CAL_SEND:
			{
				// This is a send of a frame
				DL_Frame* frame =
						(DL_Frame*) *((uint32_t*) rxMessage.parameters);
				uint8_t numChunks = *((uint8_t*) (rxMessage.parameters
						+ sizeof(DL_Frame*)));

				// Breakup the frame in chunks and enqueue them
				_enqueueFrameChunks(frame, numChunks);

				// Now get the next chunk to send
				txMessage.paramLength = 1;
				txMessage.parameters = _getNextEnqueuedChunkOnIfx(frame->ifx);
				txMessage.type = CAL_SEND;

				// Send the message
				if (!xQueueSend(vPmdDownstreamQueue_handle, &txMessage,
						portMAX_DELAY))
				{
					// If the send to the PMD fails, log the error using the diagnostic tool
					//TODO: Add support to the diagnostic tool
				}
			}
				break;

			default:
				break;
			}

			// Free parameters
			calFree(rxMessage.parameters);
		}
	}
}

void vPlcpUpstreamTask(void* pvParameters)
{
	// The input parameter of the task is not used
	calUnused(pvParameters);

	// This task manages the messages received from the PMD level (chunks)
	vPlcpUpstreamQueue_handle = xQueueCreate(IFX_TYPES_COUNT*2,
			sizeof(FREERTOS_CAL_Message));

	// Declare two messages
	FREERTOS_CAL_Message rxMessage;
	FREERTOS_CAL_Message txMessage;

	// Chunk
	PMD_Chunk* receivedChunk;
	for (;;)
	{
		if (xQueueReceive(vPlcpUpstreamQueue_handle, &rxMessage, portMAX_DELAY))
		{
			// Copy the pointer to the receivedChunk
			receivedChunk = (PMD_Chunk*) rxMessage.parameters;

			switch (rxMessage.type)
			{
			case CAL_SENT:
			{
				if (receivedChunk->isLastChunk == CAL_YES)
				{
					// If this chunk is the last one, notify the DATALINK layer that a frame has been completely sent on this interface
					txMessage.type = CAL_SENT;
					txMessage.paramLength = 1;
					CAL_InterfaceNumber* ifxNumber = calMalloc(
							sizeof(CAL_InterfaceNumber));
					*ifxNumber = receivedChunk->pmdIfx->ifxNumber;
					txMessage.parameters = ifxNumber;

					// Deallocate the received chunk
					_deAllocateChunk(receivedChunk);

					// Enqueue the message to the DATALINK
					if (!xQueueSend(vDlUpstreamQueue_handle, &txMessage,
							portMAX_DELAY))
					{
						// If the send to the DATALINK fails, log the error using the diagnostic tool
						//TODO: Add support to the diagnostic tool
					}
				}
				else
				{
					// Deallocate the received chunk
					_deAllocateChunk(receivedChunk);

					// The chunk sent is not the last one, so we have other chunks into the queue ready to be sent
					txMessage.paramLength = 1;
					txMessage.parameters = _getNextEnqueuedChunkOnIfx(
							receivedChunk->pmdIfx->ifxNumber);
					txMessage.type = CAL_SEND;

					// Enqueue the message to the PMD
					if (!xQueueSend(vPmdDownstreamQueue_handle, &txMessage,
							portMAX_DELAY))
					{
						// If the send to the PMD fails, log the error using the diagnostic tool
						//TODO: Add support to the diagnostic tool
					}
				}
			}
				break;
			case CAL_RECEIVED:
			{
				// Store the ifxNumber
				CAL_InterfaceNumber ifxNumber = receivedChunk->pmdIfx->ifxNumber;

				// Get the status of the interface
				PLCP_ReceiveStatus plcpRxStatus = _getReceiveStatusOnIfx(
						ifxNumber);

				if (plcpRxStatus == PLCP_RX_HEADER_EXPECTED)
				{
					// An header is expected, so check if this chunk is an header
					if (isHeader(receivedChunk->data) == CAL_YES)
					{
						// Enqueue the received chunk (header)
						_enqueueReceivedChunk(receivedChunk);

						// We should try to build the frame, because there should be also frame with length 1 chunk (only header)
						DL_Frame* frame = _buildReceivedFrameOnIfx(ifxNumber);

						// If the _buildReceivedFrameOnQueue has built the frame correctly (all frame's chunks have been received)
						if (frame != NULL)
						{
							// Set the interface to the DL_Frame
							frame->ifx = ifxNumber;

							txMessage.type = CAL_RECEIVED;
							txMessage.paramLength = 1;
							txMessage.parameters = frame;

							// Send the message to the DATALINK
							if (!xQueueSend(vDlUpstreamQueue_handle, &txMessage,
									portMAX_DELAY))
							{
								// If the send to the DATALINK fails, log the error using the diagnostic tool
								//TODO: Add support to the diagnostic tool
							}
						}
						else
						{
							// This chunk is an header, so change the FSM status
							_setReceiveStatusOnIfx(ifxNumber,
									PLCP_RX_DATA_EXPECTED);
						}
					}
					else
					{
						// The chunk is not an header, but an header was expected... so reject it.
						_deAllocateChunk(receivedChunk);

						// Wait for a new header, so we don't change the FSM status
					}
				}
				else if (plcpRxStatus == PLCP_RX_DATA_EXPECTED)
				{
					// Check if the arrived chunk is a normal data chunk
					if (isHeader(receivedChunk->data) == CAL_NO)
					{
						// Ok, the received chunk isn't an header, so try to build the frame

						// Enqueue the received chunk
						_enqueueReceivedChunk(receivedChunk);

						// Try to build the frame
						DL_Frame* frame = _buildReceivedFrameOnIfx(ifxNumber);

						// If the _buildReceivedFrameOnQueue has built the frame correctly (all frame's chunks have been received)
						if (frame != NULL)
						{
							// Set the interface to the DL_Frame
							frame->ifx = ifxNumber;

							// Change the status of the receive process (because we now expect an header)
							_setReceiveStatusOnIfx(ifxNumber,
									PLCP_RX_HEADER_EXPECTED);

							txMessage.type = CAL_RECEIVED;
							txMessage.paramLength = 1;
							txMessage.parameters = frame;

							// Send the message to the DATALINK
							if (!xQueueSend(vDlUpstreamQueue_handle, &txMessage,
									portMAX_DELAY))
							{
								// If the send to the DATALINK fails, log the error using the diagnostic tool
								//TODO: Add support to the diagnostic tool
							}
						}
					}
					else
					{
						// We have received a new header when it was not expected
						// Clean the queue for the previous received chunks (all discarded and rejected)
						// TODO: optionally report a frame receive error to the diagnostic tool
						_cleanReceivedChunksOnIfx(ifxNumber);

						// Enqueue the received chunk (header)
						_enqueueReceivedChunk(receivedChunk);

						// Don't change the rx FSM status, because we now still expect data chunks
					}
				}

				// Send a new CAL_RECEIVE msg to the PMD layer in order to receive new chunks on this interface
				txMessage.type = CAL_RECEIVE;
				txMessage.paramLength = 1;
				txMessage.parameters = _allocateReceiveChunkForIfx(ifxNumber);

				// Send the message to the PMD
				if (!xQueueSend(vPmdDownstreamQueue_handle, &txMessage,
						portMAX_DELAY))
				{
					// If the send to the PMD fails, log the error using the diagnostic tool
					//TODO: Add support to the diagnostic tool
				}
			}
				break;

			case CAL_SEND_ERROR:
			{
				// Clean all chunks remained to send
				_cleanSendChunksOnIfx(receivedChunk->pmdIfx->ifxNumber);

				// Deallocate this chunk
				_deAllocateChunk(receivedChunk);

				// (Re)Set the rxStatus to header expected
				_setReceiveStatusOnIfx(receivedChunk->pmdIfx->ifxNumber,
						PLCP_RX_HEADER_EXPECTED);

				// Notify the datalink layer about the SEND_ERROR
				txMessage.type = CAL_SEND_ERROR;
				txMessage.paramLength = 1;
				CAL_InterfaceNumber* ifxNumber = calMalloc(
						sizeof(CAL_InterfaceNumber));
				*ifxNumber = receivedChunk->pmdIfx->ifxNumber;
				txMessage.parameters = ifxNumber;

				// Enqueue the message to the DATALINK
				if (!xQueueSend(vDlUpstreamQueue_handle, &txMessage,
						portMAX_DELAY))
				{
					// If the send to the DATALINK fails, log the error using the diagnostic tool
					//TODO: Add support to the diagnostic tool
				}

			}
				break;

			case CAL_RECEIVE_ERROR:
			{
				// Store the ifxNumber
				CAL_InterfaceNumber ifxNumber = receivedChunk->pmdIfx->ifxNumber;

				// Dequeue and deallocate all received chunks
				_cleanReceivedChunksOnIfx(ifxNumber);

				// Deallocate the just received chunk
				_deAllocateChunk(receivedChunk);

				// Send a new CAL_RECEIVE msg to the PMD layer in order to receive new chunks on this interface
				txMessage.type = CAL_RECEIVE;
				txMessage.paramLength = 1;
				txMessage.parameters = _allocateReceiveChunkForIfx(ifxNumber);

				// Send the message with the new freshly created chunk to the PMD
				if (!xQueueSend(vPmdDownstreamQueue_handle, &txMessage,
						portMAX_DELAY))
				{
					// If the send to the PMD fails, log the error using the diagnostic tool
					//TODO: Add support to the diagnostic tool
				}
			}

				break;

			default:
				break;
			}
		}
	}

}
#endif

/**
 * @}
 */
