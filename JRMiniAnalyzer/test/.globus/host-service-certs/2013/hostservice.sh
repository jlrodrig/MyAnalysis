#!/bin/sh
# To create a new set of certs run this one command with the 
# host-service-certs.txt file as argument from quine

osg-gridadmin-cert-request -f host-service-certs.txt

# For some reason the LoadTests run by Phedex don't like service certificates
# for bestman they want the host cert to be copied as a bestmancert.pem... 

mkdir -p fiupg/rsv
mkdir -p fiupg/http
mv fiupg.hep.fiu.edu-key.pem fiupg/hostkey.pem
mv fiupg.hep.fiu.edu.pem fiupg/hostcert.pem
mv http-fiupg.hep.fiu.edu-key.pem fiupg/http/httpkey.pem
mv http-fiupg.hep.fiu.edu.pem fiupg/http/httpcert.pem
mv rsv-fiupg.hep.fiu.edu-key.pem fiupg/rsv/rsvkey.pem
mv rsv-fiupg.hep.fiu.edu.pem fiupg/rsv/rsvcert.pem

mkdir -p rocks/http
mv http-rocks.hep.fiu.edu-key.pem rocks/http/httpkey.pem
mv http-rocks.hep.fiu.edu.pem rocks/http/httpcert.pem
mv rocks.hep.fiu.edu-key.pem rocks/hostkey.pem
mv rocks.hep.fiu.edu.pem rocks/hostcert.pem

mkdir -p srm/bestman
cp srm.hep.fiu.edu-key.pem srm/bestman/bestmankey.pem
cp srm.hep.fiu.edu.pem srm/bestman/bestmancert.pem
mv srm.hep.fiu.edu-key.pem srm/hostkey.pem
mv srm.hep.fiu.edu.pem srm/hostcert.pem

