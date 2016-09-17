
Open page:

http://www.douban.com/contacts/rlist

Paste following code on console:

javascript:(function(){var t=0,n=$("h1").text().split(/\(|\)/)[1],total=parseInt(n/20);v=new Array();function test(){n2 = parseInt($("p.pl2 a").text().split(/\(|\)/)[1]/20);for(j=0;j<=n2;j++){$.get("/contacts/list?tag=0&start="+(j*20),function(dat){$(".info a",dat).each(function(){for(k=0;k<v.length;k++){if(v[k]==$(this).attr("href")){break;}}if(k==v.length){$("body").prepend($(this)).prepend("&nbsp;")}})})} }for(i=0;i<=total;i++){$.get("/contacts/rlist?start="+(20*i), function(dat){$(".info a",dat).each(function(){v.push($(this).attr("href"));t++;if(t==n){test()}});})}})()

u will see.


Ref: https://www.douban.com/note/188133704/
