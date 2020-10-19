#!/usr/bin/env python
"""
UnstructuredGrid
"""
"""

Copyright 2001 Pearu Peterson all rights reserved,
Pearu Peterson <pearu@ioc.ee>          
Permission to use, modify, and distribute this software is given under the
terms of the LGPL.  See http://www.fsf.org

NO WARRANTY IS EXPRESSED OR IMPLIED.  USE AT YOUR OWN RISK.
$Revision: 1.6 $
$Date: 2003-01-26 10:05:27 $
Pearu Peterson
"""

import DataSet
import common

class UnstructuredGrid(DataSet.DataSet):
    """
    Usage:
      UnstructuredGrid(<sequence of 3-tuples of points>,
                       vertex = <sequence [of 1-sequences]>
                       poly_vertex = <sequence of n-sequences>,
                       line = <sequence of 2-sequences>,
                       poly_line = <sequence of n-sequences>,
                       triangle = <sequence of 3-sequences>,
                       triangle_strip = <sequence of n-sequences>,
                       polygon = <sequence of n-sequences>,
                       pixel = <sequence of 4-sequences>,
                       quad = <sequence of 4-sequences>,
                       tetra = <sequence of 4-sequences>,
                       voxel = <sequence of 8-sequences>,
                       hexahedron = <sequence of 8-sequences>,
                       wedge = <sequence of 6-sequences>,
                       pyramid = <sequence of 5-sequences>
                       )
    Attributes:
      points
      vertex
      poly_vertex, line, poly_line, triangle, triangle_strip,
      polygon, pixel, quad, tetra, voxel, hexahedron, wedge, pyramid
    Public methods:
      get_size()
      get_cell_size()
      to_string(format = 'ascii')
      get_points()
      <DataSetAttr class>(...)
    """
    _vtk_cell_types_map = {'vertex':1,'poly_vertex':2,'line':3,'poly_line':4,
                           'triangle':5,'triangle_strip':6,'polygon':7,'pixel':8,
                           'quad':9,'tetra':10,'voxel':11,'hexahedron':12,
                           'wedge':13,'pyramid':14}
    _vtk_cell_nums_map = {'vertex':1,'poly_vertex':-1,'line':2,'poly_line':-1,
                           'triangle':3,'triangle_strip':-1,'polygon':-1,'pixel':4,
                           'quad':4,'tetra':4,'voxel':8,'hexahedron':8,
                           'wedge':6,'pyramid':5}
    _vtk_cell_types_imap = {1:'vertex',2:'poly_vertex',3:'line',4:'poly_line',
                            5:'triangle',6:'triangle_strip',7:'polygon',
                            8:'pixel',9:'quad',10:'tetra',11:'voxel',12:'hexahedron',
                            13:'wedge',14:'pyramid'}
    def __init__(self,points,vertex=[],poly_vertex=[],line=[],poly_line=[],
                 triangle=[],triangle_strip=[],polygon=[],pixel=[],
                 quad=[],tetra=[],voxel=[],hexahedron=[],wedge=[],pyramid=[]):
        self.points = self.get_3_tuple_list(points,(0,0,0))
        sz = len(self.points)
        for k in self._vtk_cell_types_map.keys():
            exec 'self.%s = self.get_seq_seq(%s,[])'%(k,k)
            if k=='vertex':
                r = []
                for v in self.vertex:
                    r += map(lambda a:[a],v)
                self.vertex = r
            if self._check_int_seq(getattr(self,k),sz):
                raise ValueError,'In cell %s: must be (seq of seq|seq) integers less than %s'%(k,sz)
        for k,n in self._vtk_cell_nums_map.items():
            if n==-1: continue
            kv = getattr(self,k)
            if kv==[] or kv[0]==[]: continue
            for v in kv:
                if len(v)!=n:
                    raise ValueError,'Cell %s requires exactly %s points but got %s: %s'%(`k`,n,len(v),v)

    def to_string(self,format='ascii'):
        t = self.get_datatype(self.points)
        ret = ['DATASET UNSTRUCTURED_GRID',
               'POINTS %s %s'%(self.get_size(),t),
               self.seq_to_string(self.points,format,t)]
        tps = []
        r = []
        sz = 0
        for k in self._vtk_cell_types_map.keys():
            kv = getattr(self,k)
            if kv==[] or kv[0]==[]: continue
            s = self.seq_to_string([[len(v)]+list(v) for v in kv],format,'int')
            r .append(s)
            for v in kv:
                tps.append(self._vtk_cell_types_map[k])
                sz += len(v)+1
        sep = (format=='ascii' and '\n') or (format=='binary' and '')
        r = sep.join(r)
        ret += ['CELLS %s %s'%(len(tps),sz),
                r,
                'CELL_TYPES %s'%(len(tps)),
                self.seq_to_string(tps,format,'int')]
        return '\n'.join(ret)

    def get_cell_size(self):
        sz = 0
        for k in self._vtk_cell_types_map.keys():
            kv = getattr(self,k)
            if kv==[] or kv[0]==[]: continue
            sz += len(kv)
        return sz
    def get_points(self):
        return self.points

def unstructured_grid_fromfile(f,self):
    l = common._getline(f)
    k,n,datatype = [s.strip().lower() for s in l.split(' ')]
    if k!='points':
        raise ValueError, 'expected points but got %s'%(`k`)
    n = eval(n)
    assert datatype in ['bit','unsigned_char','char','unsigned_short','short','unsigned_int','int','unsigned_long','long','float','double'],`datatype`
    points = []
    self.message('\tgetting %s points'%n)
    while len(points) < 3*n:
        points += map(eval,common._getline(f).split(' '))
    assert len(points)==3*n

    l = common._getline(f).split(' ')
    assert len(l)==3 and l[0].strip().lower() == 'cells',`l`
    n = eval(l[1])
    size = eval(l[2])
    lst = []
    self.message('\tgetting %s cell indexes'%size)
    while len(lst) < size:
        lst += map(eval,common._getline(f).split(' '))
    assert len(lst)==size
    lst2 = []
    j = 0
    for i in range(n):
        lst2.append(lst[j+1:j+lst[j]+1])
        j += lst[j]+1
    l = common._getline(f).split(' ')
    assert len(l)==2 and l[0].strip().lower() == 'cell_types' and eval(l[1])==n,`l`
    tps = []
    self.message('\tgetting %s cell types'%n)
    while len(tps) < n:
        tps += map(eval,common._getline(f).split(' '))
    assert len(tps)==n
    dict = {}
    for i,t in zip(lst2,tps):
        k = UnstructuredGrid._vtk_cell_types_imap[t]
        if not dict.has_key(k):
            dict[k] = []
        dict[k].append(i)
    self.message('\tdone')
    return UnstructuredGrid(points,**dict),common._getline(f)

if __name__ == "__main__":
    print UnstructuredGrid([[1,2],[2,4],3,5],
                           line = [[2,3],[1,2],[2,3]],
                           vertex=2)
