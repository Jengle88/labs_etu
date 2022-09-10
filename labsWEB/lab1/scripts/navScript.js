// let input1 = document.getElementById("name_input")
// let input2 = document.getElementById("input2")
// if (input1 != null && input2 != null) {
//     input2.value = input1.value
// }
// // document.getElementById("button1").onclick = function () {
// //
// // }

function toGameScreen() {
    let input = document.getElementById("name_input")
    if (input && input.value) {
        localStorage["curr_player_name"] = input.value
    } else {
        localStorage["curr_player_name"] = "Player 1"
    }
    document.getElementById("start_screen").style.display = "none"
    document.getElementById("game_screen").style.display = "flex"
    gameCycle = new GameCycle()
    gameCycle.addKeyListener()
    UIEditor.drawTetrisField()
}

function toStartScreen() {
    gameCycle.removeKeyListener()
    let playerName = localStorage["curr_player_name"]
    saveRecordToLeaderboard(playerName);
    document.getElementById("game_screen").style.display = "none"
    document.getElementById("start_screen").style.display = "block"
    UIEditor.clearTetrisField()
}




