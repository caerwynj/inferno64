#!/sh/bin
export PATH=$PWD/Linux/amd64/bin:$PATH

# execute mk-dis-folders.sh to create the expected missing folders

# edit mkconfig
#      the ROOT variable must be a hardcoded value because
#      nested mkfiles would reexpande it
#      also change $objtype by amd64

# execute makemk.sh

# for cleanup execute the line shown bellow
#mk nuke

# to make it all after thre previous steps have been done
mk install
