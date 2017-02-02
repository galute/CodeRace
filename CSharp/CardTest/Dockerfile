FROM mono:4.6.1
ADD ./CardTest/bin/Release /app
ADD ./temp.txt .
WORKDIR /app
ENTRYPOINT ["mono", "CardTest.exe"]

