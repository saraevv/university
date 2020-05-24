let circles = document.querySelectorAll('[id=circle]');

for (let circle of circles) {
	circle.addEventListener('mouseout',function(event){
		event.target.style.backgroundColor="#DC143C";
	}, false);
	circle.addEventListener('mouseover',function(event){
		event.target.style.background="#32CD32";
	}, false);
}