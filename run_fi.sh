make > dump
cd ../carol-fi
./fault_injector.py -c ../linearRegression/lreg.conf -i 10
cd scripts
./faultinj_parser.py
rm -rf dump
