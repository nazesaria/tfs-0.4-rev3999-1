# tfs-0.4-rev3999-1
Best The Forgotten Server for Otserv Custom/Global (accept scripts all tfs 0.x, all otx +, all tfs 1.X)

How compile in ubuntu 18:
Install libs:
        $ sudo apt install -y autoconf build-essential pkg-config automake libboost-all-dev libgmp3-dev libxml2-dev libl
ua5.1-0-dev libmysqlclient-dev libssl-dev libsqlite3-dev libcrypto++-dev

in "~tfs-0.4-rev3999-1"
        $ chmod -R 777 src
        $ cd src

in "~tfs-0.4-rev3999-1/src"
        $ ./autogen.sh && ./configure --enable-sqlite --enable-mysql --enable-root-permission --enable-server-diag && ./
build.sh

Install Haguichi:
	sudo add-apt-repository ppa:webupd8team/haguichi && sudo apt-get update && sudo apt-get install haguichi

