// let input1 = document.getElementById("name_input")
// let input2 = document.getElementById("input2")
// if (input1 != null && input2 != null) {
//     input2.value = input1.value
// }
// // document.getElementById("button1").onclick = function () {
// //
// // }

function toGameScreen() {
    document.getElementById("start_screen").style.display = "none"
    document.getElementById("game_screen").style.display = "flex"
    drawTetrisField()
}

function toStartScreen() {
    document.getElementById("game_screen").style.display = "none"
    document.getElementById("start_screen").style.display = "block"
    clearTetrisField()
}




