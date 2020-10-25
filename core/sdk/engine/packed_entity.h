//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
// $NoKeywords: $
//=============================================================================//
#if !defined( PACKED_ENTITY_H )
#define PACKED_ENTITY_H
#ifdef _WIN32
#pragma once
#endif

#include <const.h>
#include <utlvector.h>
#include "changeframelist.h"

enum
{
	ENTITY_SENTINEL = 9999	// larger number than any real entity number
};

#define	FLAG_IS_COMPRESSED	(1<<31)

class CSendProxyRecipients;
class SendTable;
class RecvTable;
class ServerClass;
class ClientClass;

class PackedEntity
{
public:
	PackedEntity()
	{
		m_pData = NULL;
		m_pChangeFrameList = NULL;
		m_nSnapshotCreationTick = 0;
		m_nShouldCheckCreationTick = 0;
	}

	~PackedEntity()
	{
		FreeData();

		if (m_pChangeFrameList)
		{
			m_pChangeFrameList->Release();
			m_pChangeFrameList = NULL;
		}
	}

	void FreeData() {
		if (m_pData)
		{
			free(m_pData);
			m_pData = NULL;
		}
	}

public:

	ServerClass *m_pServerClass;	// Valid on the server
	ClientClass	*m_pClientClass;	// Valid on the client

	int			m_nEntityIndex;		// Entity index.
	int			m_ReferenceCount;	// reference count;

private:

	CUtlVector<CSendProxyRecipients *>	m_Recipients;

	void				*m_pData;				// Packed data.
	int					m_nBits;				// Number of bits used to encode.
	IChangeFrameList	*m_pChangeFrameList;	// Only the most current 

												// This is the tick this PackedEntity was created on
	unsigned int		m_nSnapshotCreationTick : 31;
	unsigned int		m_nShouldCheckCreationTick : 1;
};

#endif // PACKED_ENTITY_H
