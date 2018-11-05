FOLDER=duplication
make > dump
cd ../../carol-fi
rm -rf logs
./fault_injector.py -c ../linearRegression/$FOLDER/lreg.conf -i 300 -d /tmp/lreg/detected.log
for i in $(ls logs); do
	rsync -av logs/$i/* ../linearRegression/$FOLDER/logs/$i/ > dump
done
cd ../linearRegression/$FOLDER
./faultinj_parser.py logs
mv $FOLDER_*.csv faultReport
rm -rf dump

