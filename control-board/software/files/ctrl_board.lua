
require( "unclasslib" )
require( "luactrlboardio" )

local CMD_DATA = 0
local CMD_FUNC = 1

local FUNC_VERSION     = 1
local FUNC_GPIO_EN     = 2
local FUNC_GPIO_CONFIG = 3
local FUNC_GPIO_SET    = 4
local FUNC_GPIO        = 5

local FUNC_I2C_STATUS = 10
local FUNC_I2C_EN     = 11
local FUNC_I2C_CONFIG = 12
local FUNC_I2C_IO     = 13
local FUNC_I2C_RESULT = 14


CtrlBoard = class()

function CtrlBoard:__init()
    self.dev = luactrlboardio.create()
    
    self.GPIO_AF   = 0x00
    self.GPIO_INF  = 0x04
    self.GPIO_IPD  = 0x28
    self.GPIO_IPU  = 0x48
    self.GPIO_OOD  = 0x14
    self.GPIO_OPP  = 0x10
    self.GPIO_AFOD = 0x1C
    self.GPIO_AFPP = 0x18
end

function CtrlBoard:open( stri )
    local res = self.dev:open( stri )
    return res
end

function CtrlBoard:close()
    self.dev:close()
end

function CtrlBoard:isOpen()
    local res = self.dev:isOpen()
    return res
end

function CtrlBoard:putUInt8( val )
    local res = self.dev:putUInt8( val )
    return res
end

function CtrlBoard:putUInt16( val )
    local res = self.dev:putUInt16( val )
    return res
end

function CtrlBoard:uptUInt32( val )
    local res = self.dev:putUInt32
    return res
end

function CtrlBoard:execFunc( index )
    local res = self.dev:execFunc( index )
    return res
end

function CtrlBoard:readQueue( maxSize )
    local t = self.dev:readQueue( maxSize )
    return t
end

function CtrlBoard:version()
    self.dev:execFunc( FUNC_VERSION )
    local t = self.dev:readQueue( 2 )
    if ( #t < 2 ) then
        return nil, "Failed to read version"
    end
    local res = t[1] + t[2] * 256
    return res
end

function CtrlBoard:gpioEn( index, en )
    self.dev:putUInt8( index )
    self.dev:putUInt8( en and 1 or 0 )
    self.dev:execFunc( FUNC_GPIO_EN )
    return true
end

function CtrlBoard:gpioConfig( index, pins, mode )
    self.dev:putUInt8( index )
    self.dev:putUInt16( pins )
    self.dev:putUInt8( mode )
    self.dev:execFunc( FUNC_GPIO_CONFIG )
    return true
end

function CtrlBoard:gpioSet( index, pins, vals )
    self.dev:putUInt8( index )
    self.dev:putUInt16( pins )
    self.dev:putUInt16( vals )
    self.dev:execFunc( FUNC_GPIO_SET )
    return true
end

function CtrlBoard:gpio( index )
    self.dev:putUInt8( index )
    self.dev:execFunc( FUNC_GPIO )
    local t = self.dev:readQueue( 2 )
    if ( #t < 2 ) then
        return nil, "ERROR: Failed to get GPIO state"
    end
    local res = t[1] + t[2] * 256
    return res
end




