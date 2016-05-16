var button = B6;
var led = A6;

setInterval(function() {
  if(digitalRead(button) == 1){
    digitalWrite(led,true);
  }else{
    digitalWrite(led,false);}
}, 20);