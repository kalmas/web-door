var red = function () {
  $('body').css('background-color', '#FF4040');
};

var green = function () {
  $('body').css('background-color', '#00DD2F');
};

var open = function () {
  $.ajax({
  	type: "POST",
  	url: '/open',
  	success: function () {
  	  isOpen = true;
  	  green();
  	  setTimeout(function () {
  	  	red();
  	  	isOpen = false;
  	  }, 2000);
  	}
  });
};

var isOpen = false;

$(document).ready(function () {
  $(document).click(function () {
  	if (! isOpen) {
  	  open();
  	}
  });
});
