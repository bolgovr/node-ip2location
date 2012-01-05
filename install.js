var spawn = require('child_process').spawn;
var builder = spawn('node-waf',['configure','build']);
builder.stdout.on('data',function(data){
    process.stdout.write(data);
});

builder.stderr.on('data',function(data){
    process.stdout.write(data);
});
builder.on('exit',function(code){
   process.stdout.write('building finished with code '+code+'\r\n');
});
