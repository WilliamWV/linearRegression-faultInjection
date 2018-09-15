make > dump
cd ../carol-fi
./fault_injector.py -c ../linearRegression/lreg.conf -i 500
cd scripts
./faultinj_parser.py
cp scripts_*.csv ../../linearRegression/faultReport
cd ../../linearRegression
rm -rf dump

