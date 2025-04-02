import os
import sys
import rtconfig
import platform

if os.getenv('RTT_ROOT'):
    RTT_ROOT = os.getenv('RTT_ROOT')
    print(RTT_ROOT)
else:
    RTT_ROOT = os.path.normpath(os.getcwd() + '/rt-thread')

sys.path = sys.path + [os.path.join(RTT_ROOT, 'tools')]
try:
    from building import *
except:
    print('Cannot found RT-Thread root directory, please check RTT_ROOT')
    print(RTT_ROOT)
    exit(-1)

# TARGET = 'rt-thread.' + rtconfig.TARGET_EXT
if platform.system() == "Windows":
    TARGET = 'out\\rtthread.' + rtconfig.TARGET_EXT
else:
    TARGET = 'out/rtthread.' + rtconfig.TARGET_EXT

DefaultEnvironment(tools=[])
env = Environment(tools = ['mingw'],
    AS = rtconfig.AS, ASFLAGS = rtconfig.AFLAGS,
    CC = rtconfig.CC, CFLAGS = rtconfig.CFLAGS,
    AR = rtconfig.AR, ARFLAGS = '-rc',
    CXX = rtconfig.CXX, CXXFLAGS = rtconfig.CXXFLAGS,
    LINK = rtconfig.LINK, LINKFLAGS = rtconfig.LFLAGS)
env.PrependENVPath('PATH', rtconfig.EXEC_PATH)

Export('RTT_ROOT')
Export('rtconfig')
'''
SDK_ROOT = os.path.abspath('./')

if os.path.exists(SDK_ROOT + '/board'):
    libraries_path_prefix = SDK_ROOT + '/board'
else:
    libraries_path_prefix = os.path.dirname(SDK_ROOT) + '/board'
'''
# prepare building environment
objs = PrepareBuilding(env, RTT_ROOT, has_libcpu=False)
'''
rtconfig.BSP_LIBRARY_TYPE = 'STM32F1xx_HAL'

# 显式添加编译
objs.extend(SConscript(os.path.join(libraries_path_prefix, 'SConscript'), variant_dir='build/board/', duplicate=0))
objs.extend(SConscript(os.path.join(libraries_path_prefix, 'stm_sdk', 'SConscript'), variant_dir='build/board/stm_sdk/', duplicate=0))
'''
# make a building
DoBuilding(TARGET, objs)
