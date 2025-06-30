while(true)
do
  EXE_ID="$(pgrep main)"
  ps -p $EXE_ID -o %cpu,%mem,cmd
  echo "------------------------\n"
  echo $EXE_ID
  sleep 1
done
