const circle = document.getElementById("circle");

const dev_x = document.getElementById("x");
const dev_y = document.getElementById("y");

let isMouseDown = false;
let x_pos = 0;
let y_pos = 0;

const clamp = (val, min, max) => Math.min(Math.max(val, min), max)

dev_x.addEventListener("blur", (e) => {
  if (isFinite(parseInt(e.target.value))) {
    x_pos = parseInt(e.target.value);
    post_cords();
  }
})

dev_y.addEventListener("blur", (e) => {
  if (isFinite(parseInt(e.target.value))) {
    y_pos = parseInt(e.target.value);
    post_cords();
  }
  
});

function post_cords() {
  //send cords to the server
  fetch(
    "/api/cords", {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
        // yeah its lazy asf
      body: JSON.stringify({"mouseX": clamp( x_pos + 125, 0, 3840), "mouseY": clamp(y_pos + 150, 0, 2048)}),
    }
  );
}
function update_stats(event) {
  y_pos = event.clientY - 150;
  x_pos = event.clientX - 125;

  circle.style.top = `${y_pos}px`;
  circle.style.left = `${x_pos}px`;

  x.innerText = `x: ${clamp( x_pos + 125, 0, 3840)}`;
  y.innerText = `x: ${clamp(y_pos + 150, 0, 2048)}`;

  dev_x.value = `x: ${x_pos}`;
  dev_y.value = `y: ${y_pos}`;
}

function mouse_move(event) {
  console.log("Mouse moved while held down at:", event.clientX, event.clientY);
  update_stats(event);

  post_cords();
}

document.addEventListener("mousedown", (event) => {
  isMouseDown = true;

  update_stats(event);

  circle.style.opacity = "100%";
  post_cords();
  
});

document.addEventListener("mousemove", (event) => {
  if (isMouseDown) {
    mouse_move(event);
  }
});

document.addEventListener("mouseup", () => {
  isMouseDown = false;

  circle.style.opacity = "0%";
});