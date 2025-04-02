# for module compiling
import os
Import('RTT_ROOT')
from building import *

cwd = GetCurrentDir()
objs = []
list = os.listdir(cwd)

for d in list:
    path = os.path.join(cwd, d)
    if os.path.isfile(os.path.join(path, 'SConscript')):
        objs = objs + SConscript(os.path.join(d, 'SConscript'))
'''
# 跳过已显式处理的目录
exclude_dirs = ['board', 'stm_sdk']  # 需要跳过的目录
for d in list:
    if d in exclude_dirs:
        continue  # 跳过显式添加的目录
    path = os.path.join(cwd, d)
    if os.path.isfile(os.path.join(path, 'SConscript')):
        objs = objs + SConscript(os.path.join(d, 'SConscript'))
'''        
Return('objs')
