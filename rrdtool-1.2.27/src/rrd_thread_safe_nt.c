/*****************************************************************************
 * RRDtool 1.2.27  Copyright by Tobi Oetiker, 1997-2008
 * This file:     Copyright 2003 Peter Stamfest <peter@stamfest.at> 
 *                             & Tobias Oetiker
 * Distributed under the GPL
 *****************************************************************************
 * rrd_thread_safe.c   Contains routines used when thread safety is required
 *                     for win32
 *****************************************************************************
 * $Id: rrd_thread_safe_nt.c 1286 2008-02-17 10:08:10Z oetiker $
 *************************************************************************** */

#include <windows.h>
#include <string.h>
/* #include <error.h> */
#include "rrd.h"
#include "rrd_tool.h"

/* Key for the thread-specific rrd_context */
static DWORD context_key;
static CRITICAL_SECTION CriticalSection; 


/* Once-only initialisation of the key */
static DWORD context_key_once = 0;


/* Free the thread-specific rrd_context - we might actually use
   rrd_free_context instead...
 */
static void context_destroy_context(void)
{
	DeleteCriticalSection(&CriticalSection);
    TlsFree(context_key);
	context_key_once=0;
}
static void context_init_context(void)
{
	if (!InterlockedExchange(&context_key_once, 1)) {
		context_key = TlsAlloc();
		InitializeCriticalSection(&CriticalSection);
		atexit(context_destroy_context);
	}
}
struct rrd_context *rrd_get_context(void) {
    struct rrd_context *ctx;
		
	context_init_context();
 
    ctx = TlsGetValue(context_key);
    if (!ctx) {
		ctx = rrd_new_context();
		TlsSetValue(context_key, ctx);
    } 
    return ctx;
}
#undef strerror
const char *rrd_strerror(int err) {
    struct rrd_context *ctx;
	context_init_context();

	ctx = rrd_get_context();

    EnterCriticalSection(&CriticalSection); 
    strncpy(ctx->lib_errstr, strerror(err), ctx->errlen);
    ctx->lib_errstr[ctx->errlen] = '\0';
    LeaveCriticalSection(&CriticalSection); 

    return ctx->lib_errstr;
}
/*
 * there much be a re-entrant version of these somewhere in win32 land
 */
struct tm* localtime_r(const time_t *timep, struct tm* result)
{
	struct tm *local;
	context_init_context();

	EnterCriticalSection(&CriticalSection);
	local = localtime(timep);
	memcpy(result,local,sizeof(struct tm));
	LeaveCriticalSection(&CriticalSection);
	return result;
}
char* ctime_r(const time_t *timep, char* result)
{
	char *local;
	context_init_context();

	EnterCriticalSection(&CriticalSection);
	local = ctime(timep);
	strcpy(result,local);
	LeaveCriticalSection(&CriticalSection);
	return result;
}

struct tm* gmtime_r(const time_t *timep, struct tm* result)
{
	struct tm *local;
	context_init_context();

	EnterCriticalSection(&CriticalSection);
	local = gmtime(timep);
	memcpy(result,local,sizeof(struct tm));
	LeaveCriticalSection(&CriticalSection);
	return result;
}

/* implementation from Apache's APR library */
char *strtok_r(char *str, const char *sep, char **last)
{
    char *token;
	context_init_context();


    if (!str)           /* subsequent call */
        str = *last;    /* start where we left off */

    /* skip characters in sep (will terminate at '\0') */
    while (*str && strchr(sep, *str))
        ++str;

    if (!*str)          /* no more tokens */
        return NULL;

    token = str;

    /* skip valid token characters to terminate token and
     * prepare for the next call (will terminate at '\0) 
     */
    *last = token + 1;
    while (**last && !strchr(sep, **last))
        ++*last;

    if (**last) {
        **last = '\0';
        ++*last;
    }

    return token;
}

