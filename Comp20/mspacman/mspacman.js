var SCREEN_WIDTH = window.innerWidth,
SCREEN_HEIGHT = window.innerHeight;

image = new Image();
image.src = "pacman10-hp-sprite.png";

var pm_start_x = 20,
pm_start_y = 115,
gh_start_x = 20,
gh_start_y = 5;

function start_game() {
	var canvas = document.getElementById('game');
		if (canvas.getContext) {
			ctx = canvas.getContext("2d");
			ctx.clearRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			
			//draw board
			ctx.drawImage(image, 322, 0, 464, 138, 0, 0, 464, 138);
			
			//draw Ms. Pac-Man
			ctx.drawImage(image, 80, 0, 20, 20, pm_start_x, pm_start_y, 20, 20);
			
			//draw ghost
			ctx.drawImage(image, 0, 80, 20, 20, gh_start_x, gh_start_y, 20, 20);
		}
	else {
		alert('Sorry, canvas is not supported on your browser!');
	}
}