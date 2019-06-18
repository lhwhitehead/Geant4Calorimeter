#source /cvmfs/uboone.opensciencegrid.org/products/setup_uboone.sh
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup geant4 v4_10_3_p03c -f Linux64bit+3.10-2.17 -q e17:prof
setup root v5_34_32 -f Linux64bit+3.10-2.17 -q e9:nu:prof
setup clhep v2_3_4_6 -q e17:prof

#setup gcc v4_9_3 -f Linux64bit+3.10-2.17
#setup git v2_4_6 -f Linux64bit+3.10-2.17
#setup python v2_7_13d -f Linux64bit+3.10-2.17

#setup eigen v3_3_3
#setup root v6_06_08 -f Linux64bit+3.10-2.17 -q e10:nu:prof
#setup geant4 v4_10_3_p03c -f Linux64bit+3.10-2.17 -q e17:prof

#setup clhep v2_3_4_6 -q e17:prof
#export LD_LIBRARY_PATH=/usera/marshall/Test/github/lib/:$LD_LIBRARY_PATH

#setup root v5_34_32 -f Linux64bit+3.10-2.17 -q e9:nu:prof
#source /usera/marshall/Test/root_v06_06_04/bin/thisroot.sh

#export PATH=/usera/marshall/Test/github/bin/:$PATH
#export LIBGL_ALWAYS_INDIRECT=1 #For visualisation within nx

# 1003  more mastersetup.sh 
# 1004  cd build/
# 1005  rm -fr *
# 1006  source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
# 1007  setup geant4 v4_10_3_p03c -f Linux64bit+3.10-2.17 -q e17:prof
# 1008  setup root v5_34_32 -f Linux64bit+3.10-2.17 -q e9:nu:prof
# 1009  cmake ..
# 1010  setup clhep v2_3_4_6 -q e17:prof
# 1011  cmake ..
# 1012  rm -fr *
# 1013  cmake ..
# 1014  make -j4 install
# 1015  vi ../mastersetup.sh 
# 1016  history
