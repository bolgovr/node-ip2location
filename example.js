var ip2loc  = require('./index.js');
var http = require('http');
var dbpath = './data/PATH-TO-IP2LOCATION.BIN';
var location = new ip2loc(dbpath);
var app = http.createServer(function(req,res){
    var randIP = [];
    randIP.push((Math.random()*255%255).toFixed());
    randIP.push((Math.random()*255%255).toFixed());
    randIP.push((Math.random()*255%255).toFixed());
    randIP.push((Math.random()*255%255).toFixed());
    var ip = randIP.join('.'); 
    var obj;
    try{
        obj = location.getIpInfo(ip);
    }catch(e){
    console.log(e.message);
        location= new ip2loc(dbpath);
    }
    if(obj&&obj.country_long){
        res.end("hello "+ip+" you are in "+obj.country_long+" ("+obj.country_short+") in region/city:"+obj.region+"/"+obj.city+" and your timezone is:"+obj.timezone);
    
    }else{
        res.end('db closed');
    }
});
    setInterval(function(){
        location.close();
    },3000);

app.listen(8080);
