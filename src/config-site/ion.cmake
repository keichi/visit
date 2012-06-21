#/apps/visit/cmake/2.8.3/linux-x86_64_gcc-4.6/bin/cmake
##
## ./svn_bin/build_visit generated host.cmake
## created: Fri Jun  8 14:43:55 EDT 2012
## system: Linux ion 3.2.0-24-generic #39-Ubuntu SMP Mon May 21 16:52:17 UTC 2012 x86_64 x86_64 x86_64 GNU/Linux
## by: js9

##
## Setup VISITHOME & VISITARCH variables.
##
SET(VISITHOME /apps/visit)
SET(VISITARCH linux-x86_64_gcc-4.6)
SET(VISIT_VERBOSE_MAKEFILE TRUE)
SET(CMAKE_INSTALL_PREFIX /apps/visit)
SET(CMAKE_BUILD_TYPE Debug CACHE STRING "")

## Compiler flags.
##
VISIT_OPTION_DEFAULT(VISIT_C_COMPILER gcc TYPE FILEPATH)
VISIT_OPTION_DEFAULT(VISIT_CXX_COMPILER g++ TYPE FILEPATH)
VISIT_OPTION_DEFAULT(VISIT_C_FLAGS " -m64 -fPIC -fvisibility=hidden" TYPE STRING)
VISIT_OPTION_DEFAULT(VISIT_CXX_FLAGS " -m64 -fPIC -fvisibility=hidden" TYPE STRING)

##############################################################
##
## Database reader plugin support libraries
##
## The HDF4, HDF5 and NetCDF libraries must be first so that
## their libdeps are defined for any plugins that need them.
##
## For libraries with LIBDEP settings, order matters.
## Libraries with LIBDEP settings that depend on other
## Library's LIBDEP settings must come after them.
##############################################################
##
##
## Specify the location of the python.
##
VISIT_OPTION_DEFAULT(VISIT_PYTHON_DIR /usr)
VISIT_OPTION_DEFAULT(PYTHON_INCLUDE_PATH /usr/include/python2.7 )
VISIT_OPTION_DEFAULT(PYTHON_LIBRARY /usr/lib/libpython2.7.so)
VISIT_OPTION_DEFAULT(PYTHON_LIBRARY_DIR /usr/lib/x86_64-linux-gnu)
VISIT_OPTION_DEFAULT(PYTHON_VERSION 2.7)

##
## Mesa
##
VISIT_OPTION_DEFAULT(VISIT_MESA_DIR ${VISITHOME}/mesa/7.8.2/${VISITARCH})


##
## VTK
##
VISIT_OPTION_DEFAULT(VISIT_VTK_DIR ${VISITHOME}/vtk/5.8.0/${VISITARCH})

##
## Specify the Qt4 binary dir. 
## (qmake is used to locate & setup Qt4 dependencies)
##
VISIT_OPTION_DEFAULT(QT_QTUITOOLS_INCLUDE_DIR /usr/include/qt4/QtUiTools)
VISIT_OPTION_DEFAULT(VISIT_QT_BIN /usr/bin)


##
## SZIP
##
VISIT_OPTION_DEFAULT(VISIT_SZIP_DIR ${VISITHOME}/szip/2.1/${VISITARCH})

##
## HDF5
##
VISIT_OPTION_DEFAULT(VISIT_HDF5_DIR ${VISITHOME}/hdf5/1.8.7/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_HDF5_LIBDEP ${VISITHOME}/szip/2.1/${VISITARCH}/lib sz /usr/lib/x86_64-linux-gnu z TYPE STRING)

##
## HDF4
##
VISIT_OPTION_DEFAULT(VISIT_HDF4_DIR ${VISITHOME}/hdf4/4.2.5/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_HDF4_LIBDEP ${VISITHOME}/szip/2.1/${VISITARCH}/lib sz ${VISITHOME}/vtk/5.8.0/${VISITARCH}/lib vtkjpeg TYPE STRING)

##
## NetCDF
##
VISIT_OPTION_DEFAULT(VISIT_NETCDF_DIR ${VISITHOME}/netcdf/4.1.1/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_NETCDF_LIBDEP HDF5_LIBRARY_DIR hdf5_hl HDF5_LIBRARY_DIR hdf5 ${VISIT_HDF5_LIBDEP} TYPE STRING)

##
## CGNS
##
VISIT_OPTION_DEFAULT(VISIT_CGNS_DIR ${VISITHOME}/cgns/3.0.8/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_CGNS_LIBDEP HDF5_LIBRARY_DIR hdf5 ${VISIT_HDF5_LIBDEP} TYPE STRING)

##
## GDAL
##
VISIT_OPTION_DEFAULT(VISIT_GDAL_DIR ${VISITHOME}/gdal/1.7.1/${VISITARCH})

##
## Exodus
##
VISIT_OPTION_DEFAULT(VISIT_EXODUSII_DIR ${VISITHOME}/exodus/4.98/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_EXODUSII_LIBDEP NETCDF_LIBRARY_DIR netcdf ${VISIT_NETCDF_LIBDEP} TYPE STRING)

##
## Boxlib
##
VISIT_OPTION_DEFAULT(VISIT_BOXLIB_DIR ${VISITHOME}/boxlib/0.1.8/${VISITARCH})

##
## CFITSIO
##
VISIT_OPTION_DEFAULT(VISIT_CFITSIO_DIR ${VISITHOME}/cfitsio/3006/${VISITARCH})

##
## H5Part
##
VISIT_OPTION_DEFAULT(VISIT_H5PART_DIR ${VISITHOME}/h5part/1.6.6/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_H5PART_LIBDEP HDF5_LIBRARY_DIR hdf5 ${VISIT_HDF5_LIBDEP} TYPE STRING)

##
## FastBit
##
VISIT_OPTION_DEFAULT(VISIT_FASTBIT_DIR ${VISITHOME}/fastbit/1.2.0/${VISITARCH})

##
## CCMIO
##
VISIT_OPTION_DEFAULT(VISIT_CCMIO_DIR ${VISITHOME}/ccmio/2.6.1/${VISITARCH})

##
## Silo
##
VISIT_OPTION_DEFAULT(VISIT_SILO_DIR ${VISITHOME}/silo/4.8/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_SILO_LIBDEP HDF5_LIBRARY_DIR hdf5 ${VISIT_HDF5_LIBDEP} TYPE STRING)

##
## Xdmf
##
VISIT_OPTION_DEFAULT(VISIT_XDMF_DIR ${VISITHOME}/Xdmf/2.1.1/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_XDMF_LIBDEP HDF5_LIBRARY_DIR hdf5   VTK_LIBRARY_DIRS vtklibxml2  TYPE STRING)
##
##
## Specify the PySide dir. 
##
VISIT_OPTION_DEFAULT(VISIT_PYSIDE_DIR ${VISITHOME}/pyside/1.0.7/${VISITARCH}/)

##
