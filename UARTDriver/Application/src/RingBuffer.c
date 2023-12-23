#include "RingBuffer.h"

bool RingBuffer_Init(RingBuffer* ringBuffer, char* dataBuffer, size_t dataBufferSize)
{
	assert(ringBuffer);
	assert(dataBuffer);
	assert(dataBufferSize > 0);

	if ((ringBuffer) && (dataBuffer) && (dataBufferSize > 0)) {
		ringBuffer->buff = dataBuffer;
		ringBuffer->capacity = dataBufferSize;
		ringBuffer->head = 0;
		ringBuffer->tail = 0;
		ringBuffer->count = 0;
		return true;
	}

	return false;
}

bool RingBuffer_Clear(RingBuffer* ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer) {
		ringBuffer->head = 0;
		ringBuffer->tail = 0;
		ringBuffer->count = 0;
		return true;
	}
	return false;
}

bool RingBuffer_IsEmpty(const RingBuffer* ringBuffer)
{
	assert(ringBuffer);
	if(ringBuffer->count == 0)
	{
		return true;
	}
	return false;
}

size_t RingBuffer_GetLen(const RingBuffer* ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer) {
		return (ringBuffer->count);
	}
	return 0;

}

size_t RingBuffer_GetCapacity(const RingBuffer* ringBuffer)
{
	assert(ringBuffer);

	if (ringBuffer) {
		return ringBuffer->capacity;
	}
	return 0;
}


bool RingBuffer_PutChar(RingBuffer* ringBuffer, char c)
{
	assert(ringBuffer);

	if (ringBuffer) {
		if (RingBuffer_GetLen(ringBuffer) == ringBuffer->capacity)
		{
			return false;
		}
		ringBuffer->buff[ringBuffer->head] = c;
		ringBuffer->head = (ringBuffer->head + 1) % ringBuffer->capacity;
		ringBuffer->count++;
		return true;
	}
	return false;
}

bool RingBuffer_GetChar(RingBuffer* ringBuffer, char* c)
{
	assert(ringBuffer);
	assert(c);

	if ((ringBuffer) && (c)) {
		if (RingBuffer_IsEmpty(ringBuffer)) 
		{
			return false;
		}
		*c = ringBuffer->buff[ringBuffer->tail];
		ringBuffer->tail = (ringBuffer->tail + 1) % ringBuffer->capacity;
		ringBuffer->count--;
		return true;
	}
	return false;
}