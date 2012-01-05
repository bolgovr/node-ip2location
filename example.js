var w = require('./build/Release/ip2locationnode.node').Location;
var http = require('http');
var dbpath = './data/IP-COUNTRY.BIN';
var ww = new w(dbpath);
var app = http.createServer(function(req,res){
    var randIP = [];
    randIP.push((Math.random()*255%255).toFixed());
    randIP.push((Math.random()*255%255).toFixed());
    randIP.push((Math.random()*255%255).toFixed());
    randIP.push((Math.random()*255%255).toFixed());
    var ip = randIP.join('.'); 
    var obj;
    try{
        obj = ww.getIpInfo(ip);
    }catch(e){
    console.log(e.message);
        ww= new w(dbpath);
    }
    if(obj&&obj.country_long){
        res.end("hello "+ip+" you are in "+obj.country_long+" ("+obj.country_short+") in region/city:"+obj.region+"/"+obj.city+" and your timezone is:"+obj.timezone);
    
    }else{
        res.end('shit happens');
    }
});
    setInterval(function(){
        ww.close();
    },3000);

app.listen(8080);
