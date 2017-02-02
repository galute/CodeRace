FROM microsoft/dotnet:1.1-runtime
ADD ./ConsoleApp/bin/Release/netcoreapp1.0 /app
ADD ./temp.txt .

WORKDIR /app
ADD ./launch.sh .
ENTRYPOINT ["dotnet", "ConsoleApp.dll"]

