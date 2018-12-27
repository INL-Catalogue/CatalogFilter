APPNAME = 'CatalogFilter'
VERSION = '0.1.0'

srcdir = '.'
blddir = 'build'

defines = []
defines.append('_DEBUG')

import subprocess
import os
import sys

def options(opt):
	opt.load('compiler_cxx')

def configure(ctx):
	ctx.load('compiler_cxx')

def build(bld):
	bld.recurse('Catlib')
	bld.program(
			source = ['./connect_mysql.cpp'],
			target = 'Connect_mysql',
			includes = ['./catlib/include', './catlib/include/catlib', './mysql_config.hpp'],
			defines  = defines,
			cxxflags = ['-O3', '-g', '-Wall', '-std=c++11'],
			#lib      = ['m', 'pthread', 'rt'],
			lib      = ['m', 'pthread', 'mysqlclient'],
			use      = ['catalog'],
	)

	bld.program(
			source = ['./main.cpp'],
			target = 'CatalogFilter',
			includes = ['./include', './catlib/include', './catlib/include/catlib'],
			defines  = defines,
			cxxflags = ['-O3', '-g', '-Wall', '-std=c++11'],
			#lib      = ['m', 'pthread', 'rt'],
			lib      = ['m', 'pthread', 'mysqlclient'],
			use      = ['catalog'],
	)

def run(r):
	subprocess.call(["./build/CatalogFilter/"])

def con(r):
	subprocess.call(["./build/Connect_mysql/"])

def shutdown(ctx):
	pass
