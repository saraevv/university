let links = document.querySelectorAll('[id=link]');

for (let link of links) {
	link.addEventListener('mouseout',function(event){
		event.target.style.color="#4682B4";
	}, false);
	link.addEventListener('mouseover',function(event){
		event.target.style.color="#008080";
	}, false);
}