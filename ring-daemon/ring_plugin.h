/*
 *  Copyright (C) 2004-2017 Savoir-faire Linux Inc.
 *
 *  Author: Guillaume Roguez <guillaume.roguez@savoirfairelinux.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.
 */

#ifndef RING_PLUGIN_H
#define RING_PLUGIN_H

#include <inttypes.h>

#ifdef __cplusplus
#  define EXTERNAL_C_LINKAGE extern "C"
#  define C_INTERFACE_START EXTERNAL_C_LINKAGE {
#  define C_INTERFACE_END }
#else
#  define C_LINKAGE
#  define C_INTERFACE_START
#  define C_INTERFACE_END
#endif

#define RING_PLUGIN_ABI_VERSION 1 /* 0 doesn't exist, considered as error */
#define RING_PLUGIN_API_VERSION 1 /* 0 doesn't exist, considered as error */

C_INTERFACE_START;

class RING_Plugin {
public:
	virtual RING_Plugin(const RING_PluginAPI *api) = 0;
	virtual void destroy() = 0;
	virtual void onEvent(RING_Event* event) = 0;
}

typedef struct RING_PluginVersion {
    /* plugin is not loadable if this number differs from one
     * stored in the plugin loader */
    uint32_t                            abi;

    /* a difference on api number may be acceptable, see the loader code */
    uint32_t                            api;
} RING_PluginVersion;

struct RING_PluginAPI;

/* RING_PluginCreateFunc parameters */
typedef struct RING_PluginObjectParams {
    const RING_PluginAPI*               pluginApi; /* this API */
    const char*                         type;
} RING_PluginObjectParams;

typedef void* (*RING_PluginCreateFunc)(RING_PluginObjectParams* params, void* closure);

typedef void (*RING_PluginDestroyFunc)(void *object, void* closure);

/* RING_PluginAPI.registerObjectFactory data */
typedef struct RING_PluginObjectFactory {
    RING_PluginVersion                  version;
    void*                               closure; /* closure for create */
    RING_PluginCreateFunc               create;
    RING_PluginDestroyFunc              destroy;
} RING_PluginObjectFactory;

/* Plugins exposed API prototype */
typedef int32_t (*RING_PluginFunc)(const RING_PluginAPI* api,
                                   const char* name,
                                   void* data);

/* RING_PluginInitFunc parameters.
 * This structure is filled by the Plugin manager.
 * For backware compatibility, never c
 */
typedef struct RING_PluginAPI {
    RING_PluginVersion                  version; /* structure version, always the first data */
    void*                               context; /* opaque structure used by next functions */

    /* API usable by plugin implementors */
    RING_PluginFunc                     registerObjectFactory;
    RING_PluginFunc                     invokeService;
} RING_PluginAPI;


typedef RING_Plugin* (*RING_PluginCreateFunc)(const RING_PluginAPI *api);

C_INTERFACE_END;

#define RING_DYN_CREATE_FUNC_NAME "RING_dynPluginCreate"
#define RING_PLUGIN_CREATE_STATIC(fname, pname) RING_PLUGIN_CREATE(fname, pname)
#define RING_PLUGIN_CREATE_DYNAMIC(pname) RING_PLUGIN_CREATE(RING_dynPluginCreate, pname)

/* Define here platform dependent way to export a declaration x to the dynamic
 * loading system.
 */

/* Default case (like POSIX/.so) */

#define RING_PLUGIN_CREATE(fname, pname) \
    EXTERNAL_C_LINKAGE RING_Plugin* fname(const RING_PluginAPI *pname)

#endif /* RING_PLUGIN_H */
