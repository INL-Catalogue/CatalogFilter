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

	bld.program(
			source = ['./filter1.cpp'],
			target = 'Filter1',
			includes = ['./include', './catlib/include', './catlib/include/catlib'],
			defines  = defines,
			cxxflags = ['-O3', '-g', '-Wall', '-std=c++11'],
			#lib      = ['m', 'pthread', 'rt'],
			lib      = ['m', 'pthread', 'mysqlclient'],
			use      = ['catalog'],
	)

	bld.program(
			source = ['./filter2.cpp'],
			target = 'Filter2',
			includes = ['./include', './catlib/include', './catlib/include/catlib'],
			defines  = defines,
			cxxflags = ['-O3', '-g', '-Wall', '-std=c++11'],
			#lib      = ['m', 'pthread', 'rt'],
			lib      = ['m', 'pthread', 'mysqlclient'],
			use      = ['catalog'],
	)

	bld.program(
			source = ['./prot_filter1.cpp'],
			target = 'Prototype1',
			includes = ['./include', './catlib/include', './catlib/include/catlib'],
			defines  = defines,
			cxxflags = ['-O3', '-g', '-Wall', '-std=c++11'],
			#lib      = ['m', 'pthread', 'rt'],
			lib      = ['m', 'pthread', 'mysqlclient'],
			use      = ['catalog'],
	)

	bld.program(
			source = ['./prot_filter2.cpp'],
			target = 'Prototype2',
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

def fl1(r):
	subprocess.call(["./build/Filter1/"])

def fl2(r):
	subprocess.call(["./build/Filter2/"])

def prot1(r):
	subprocess.call(["./build/Prototype1/"])

def prot2(r):
	subprocess.call(["./build/Prototype2/"])

def shutdown(ctx):
	pass
