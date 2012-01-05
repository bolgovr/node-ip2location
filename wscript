import os
import shutil
srcdir = os.path.abspath('.')
blddir = 'build'
target = 'ip2locationnode'


def set_options(opt):
    opt.tool_options("compiler_cxx")

def configure(conf):
    conf.check_tool("compiler_cxx")
    conf.check_tool("node_addon")
    conf.check_cxx(lib="IP2Location", mandatory=True, uselib_store='IP2Location')

def build(bld):
    obj = bld.new_task_gen("cxx", "shlib", "node_addon")
    obj.cxxflags = ["-g", "-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE", "-Wall"]
    obj.target = "ip2locationnode"
    obj.uselib = "IP2Location"
    obj.source = "src/ip2locationnode.cc"
    bld.add_post_fun(move_ready)

def move_ready(context,target=target):
    filename = '%s.node' % target
    from_path = os.path.join(srcdir,blddir,'Release',filename)
    to_path = os.path.join(srcdir,'lib',filename)
    if os.path.exists(from_path):
        os.rename(from_path, to_path)
        shutil.rmtree(blddir)
