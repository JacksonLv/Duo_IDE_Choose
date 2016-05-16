var analogbutton = A3;
var fan = B5;
var a;

setInterval(function() {
    a = analogRead(analogbutton);
    analogWrite(fan,a);
}, 20);