sudo mkdir /usr/include/agl/mapping
sudo cp -Rap *.h /usr/include/agl/mapping/
make release
sudo cp -Rap ../lib/*.so /usr/lib/
