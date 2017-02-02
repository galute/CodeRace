var fs = require('fs');
var numbers = [];

fs.readFile('./temp.txt', function (err, logData)
{
    if (err)
    {
        throw err;
    }
    var starttime = new Date().getTime();
    var text = logData.toString();
            
    var results = {};
            
    var lines = text.split('\n');
            
    lines.forEach(function(line)
    {
        if (line.length != 0)
        {
            reverseNumber(line);
        }
    });
            
    processNumbers();
            
    var endtime = new Date().getTime();
    var elapsed = endtime - starttime;
            
    console.log('time: ' + elapsed);
});

reverseNumber = function(line)
{
    var reversed = [];
    
    var i = line.length;
    while (i--) {
        reversed.push(parseInt(line[i]));
    }
    numbers.push(reversed);
}

processNumbers = function()
{
    numbers.forEach(function(number)
    {
        var oddacc = 0;
        var evenacc = 0;
                    
        for (var i = 0; i < 16; i++)
        {
            if (number[i] % 2 == 0 )
            {
                oddacc += number[i];
            }
            else
            {
                var even_num = number[i] * 2
                    
                if (even_num > 9)
                {
                    even_num -= 10;
                }
                    
                evenacc += even_num;
            }
        }
                    
        if ((oddacc + evenacc)%10)
        {
            console.log('Yes');
        }
        else
        {
            console.log('No');
        }
    });
}
