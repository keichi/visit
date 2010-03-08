#/usr/common/graphics/installs/visit_3rdparty/cmake/2.8.0/linux-x86_64_gcc-4.4/bin/cmake

##
## build_vist generated host.conf
## created: Mon Dec  8 17:15:07 PST 2008
## system: Linux nid04111 2.6.16.54-0.2.8_1.0000.3800.0-ss #1 SMP Tue Oct 21 16:10:08 PDT 2008 x86_64 x86_64 x86_64 GNU/Linux
## by: ghweber

##
## Set the VISITHOME environment variable.
##
SET(VISITHOME /usr/common/graphics/installs/visit_3rdparty)
SET(VISITARCH linux-x86_64_gcc-4.3)
SET(VISIT_VERBOSE_MAKEFILE TRUE)

##
## Do not build Tuvok
##
VISIT_OPTION_DEFAULT(VISIT_TUVOK OFF)

##
## Specify the location of the mesa include files and libraries.
##
VISIT_OPTION_DEFAULT(VISIT_MESA_DIR ${VISITHOME}/mesa/7.5/${VISITARCH})

##
## Specify the location of the vtk include files and libraries.
##
VISIT_OPTION_DEFAULT(VISIT_VTK_DIR ${VISITHOME}/vtk/5.0.0d/${VISITARCH}/lib/vtk-5.0)

##
## Specify the location of the qt include files and libraries.
##
VISIT_OPTION_DEFAULT(VISIT_QT_BIN ${VISITHOME}/qt/4.4.3/${VISITARCH}/bin)

##
## Specify the location of the python include and libraries.
##
VISIT_OPTION_DEFAULT(VISIT_PYTHON_DIR ${VISITHOME}/python/2.5/${VISITARCH})

## Compiler flags.
##
SET(VISIT_C_COMPILER gcc)
SET(VISIT_C_FLAGS "-m64 -fPIC -DVIZSCHEMA_DECOMPOSE_DOMAINS")
SET(VISIT_MPI_C_FLAGS "-DMPICH_IGNORE_CXX_SEEK -I/opt/mpt/default/xt/mpich2-gnu/include")
SET(VISIT_CXX_COMPILER g++)
SET(VISIT_CXX_FLAGS "-m64 -fPIC -DVIZSCHEMA_DECOMPOSE_DOMAINS")
SET(VISIT_MPI_CXX_FLAGS "-DMPICH_IGNORE_CXX_SEEK -I/opt/mpt/default/xt/mpich2-gnu/include")
# Get these via CC -v
SET(VISIT_MPI_LIBS /opt/mpt/default/xt/mpich2-gnu/lib/libmpich.a /opt/mpt/default/xt/pmi/lib/libpmi.a /opt/mpt/default/xt/util/lib/libalpslli.a /opt/mpt/default/xt/util/lib/libalpsutil.a /opt/xt-xcpe/default/lib/snos64/libportals.a pthread)
VISIT_OPTION_DEFAULT(VISIT_PARALLEL ON)
VISIT_OPTION_DEFAULT(VISIT_NOLINK_MPI_WITH_LIBRARIES ON)
VISIT_OPTION_DEFAULT(VISIT_CREATE_SOCKET_RELAY_EXECUTABLE ON)

##
## Database reader plugin support libraries
##
##############################################################

##
## Boxlib
##
VISIT_OPTION_DEFAULT(VISIT_BOXLIB2D_DIR ${VISITHOME}/boxlib/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_BOXLIB3D_DIR ${VISITHOME}/boxlib/${VISITARCH})

##
## CFITSIO
##
VISIT_OPTION_DEFAULT(VISIT_CFITSIO_DIR ${VISITHOME}/cfitsio/3006/${VISITARCH})

##
## CGNS
##
VISIT_OPTION_DEFAULT(VISIT_CGNS_DIR ${VISITHOME}/cgns/2.4/${VISITARCH})

##
## GDAL
##
VISIT_OPTION_DEFAULT(VISIT_GDAL_DIR ${VISITHOME}/gdal/1.6.3/${VISITARCH})

##
## H5Part
##
VISIT_OPTION_DEFAULT(VISIT_H5PART_DIR ${VISITHOME}/h5part/1.4.2/${VISITARCH})

##
## FastBit
##
VISIT_OPTION_DEFAULT(VISIT_FASTBIT_DIR ${VISITHOME}/fastbit/1.0.9/${VISITARCH})

##
## HDF5
##
VISIT_OPTION_DEFAULT(VISIT_HDF5_DIR ${VISITHOME}/hdf5/1.8.3/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_HDF5_LIBDEP ${VISITHOME}/szip/2.1/${VISITARCH}/lib sz)

##
## Silo
##
VISIT_OPTION_DEFAULT(VISIT_SILO_DIR ${VISITHOME}/silo/4.7/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_SILO_LIBDEP HDF5_LIBRARY_DIR hdf5 ${VISIT_HDF5_LIBDEP})

##
## NetCDF
##
VISIT_OPTION_DEFAULT(VISIT_NETCDF_DIR ${VISITHOME}/netcdf/3.6.3/${VISITARCH})

##
## SZIP
##
SET(SZIP_DIR ${VISITHOME}/szip/2.1/${VISITARCH})

##
## CCMIO
##
VISIT_OPTION_DEFAULT(VISIT_CCMIO_DIR ${VISITHOME}/ccmio/2.6.1/${VISITARCH})