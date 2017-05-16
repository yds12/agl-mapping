sudo mkdir /usr/include/agl/mapping
sudo cp -Rap *.h /usr/include/agl/mapping/
make debug
sudo cp -Rap ../lib/*.so /usr/lib/
