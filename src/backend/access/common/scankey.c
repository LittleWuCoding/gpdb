/*-------------------------------------------------------------------------
 *
 * scan.c
 *	  scan direction and key code
 *
 * Portions Copyright (c) 1996-2001, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *	  $Header: /cvsroot/pgsql/src/backend/access/common/scankey.c,v 1.19 2001/06/01 02:41:35 tgl Exp $
 *
 *-------------------------------------------------------------------------
 */

#include "postgres.h"

#include "access/skey.h"

/*
 * ScanKeyEntryIsLegal
 *		True iff the scan key entry is legal.
 */
#define ScanKeyEntryIsLegal(entry) \
( \
	AssertMacro(PointerIsValid(entry)), \
	AttributeNumberIsValid((entry)->sk_attno) \
)

/*
 * ScanKeyEntrySetIllegal
 *		Marks a scan key entry as illegal.
 */
void
ScanKeyEntrySetIllegal(ScanKey entry)
{

	Assert(PointerIsValid(entry));

	entry->sk_flags = 0;		/* just in case... */
	entry->sk_attno = InvalidAttrNumber;
	entry->sk_procedure = 0;	/* should be InvalidRegProcedure */
	entry->sk_func.fn_oid = InvalidOid;
	entry->sk_argument = (Datum) 0;
}

/*
 * ScanKeyEntryInitialize
 *		Initializes a scan key entry.
 *
 * Note:
 *		Assumes the scan key entry is valid.
 *		Assumes the intialized scan key entry will be legal.
 */
void
ScanKeyEntryInitialize(ScanKey entry,
					   bits16 flags,
					   AttrNumber attributeNumber,
					   RegProcedure procedure,
					   Datum argument)
{
	Assert(PointerIsValid(entry));

	entry->sk_flags = flags;
	entry->sk_attno = attributeNumber;
	entry->sk_procedure = procedure;
	entry->sk_argument = argument;
	fmgr_info(procedure, &entry->sk_func);

	Assert(ScanKeyEntryIsLegal(entry));
}
