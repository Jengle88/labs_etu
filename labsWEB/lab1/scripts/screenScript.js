function prepareNickname(maxCharacterInNick) {
    let playerNick = `Игрок: ${localStorage["curr_player_name"]}`.trim()
    if (playerNick.length > maxCharacterInNick)
        playerNick = playerNick.slice(0, maxCharacterInNick).concat("...")
    document.getElementById("player_name").textContent = playerNick
        .slice(0, 30)
}

function prepareScreen() {
    const maxCharacterInNick = 25
    document.getElementById("current_level").textContent = `Уровень: ${gameCycle.currLevel}`
    document.getElementById("player_score").textContent = `Счёт: ${gameCycle.gameScoreProxy.score}`
    prepareNickname(maxCharacterInNick)
}

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
    gameCycle.createField(UIEditor.fieldCanvas.clientWidth / UIEditor.squareSize, UIEditor.fieldCanvas.clientHeight / UIEditor.squareSize)
    prepareScreen()
    gameCycle.addKeyListener()
    UIEditor.drawTetrisField()
}

function toStartScreen() {
    gameCycle.removeKeyListener()
    let playerName = localStorage["curr_player_name"]
    saveRecordToLeaderboard(playerName)
    document.getElementById("game_screen").style.display = "none"
    document.getElementById("start_screen").style.display = "block"
    UIEditor.clearTetrisField()
}




