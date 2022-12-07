class ScreenScript {
    static maxCharacterInNickForGameScreen = 25
    static maxCharacterInNickForLeaderboardScreen = 40

    static URL = "https://localhost:3000"
    // FIXME: поле с тетрисом не всегда очищается

    static toGameScreen() {
        let input = document.getElementById("name_input")
        if (input && input.value) {
            localStorage["curr_player_name"] = input.value
        } else {
            localStorage["curr_player_name"] = "Player 1"
        } // FIXME
        window.location = ScreenScript.URL + "/game"

        // document.getElementById("start_screen").style.display = "none"
        // document.getElementById("leaderboard_screen").style.display = "none"
        // document.getElementById("game_screen").style.display = "flex"
        // gameCycle = new GameCycle()
        // gameCycle.createField(UIEditor.fieldCanvas.clientWidth / UIEditor.squareSize, UIEditor.fieldCanvas.clientHeight / UIEditor.squareSize)
        // ScreenScript.#prepareScreen()
        // gameCycle.addKeyListener()
        // UIEditor.drawTetrisField()
    }

    static load() {
        let canvas = document.getElementById("game_field")
        let context = canvas.getContext("2d")
        let image = new Image(300, 300)
        image.src = "images/city_level1(1).png"
        context.drawImage(image, 0, 0, 300, 300)
    }

    static toStartScreen() {
        if (/*gameCycle*/true) { // FIXME
            let playerName = localStorage["curr_player_name"]
            saveRecordToLeaderboard(playerName)
            // gameCycle.removeKeyListener() // FIXME
            // UIEditor.clearTetrisField()
        }
        // document.getElementById("game_screen").style.display = "none"
        document.getElementById("leaderboard_screen").style.display = "none"
        document.getElementById("start_screen").style.display = "flex"
    }

    static toLeaderboardScreen() {
        let input = document.getElementById("name_input")
        if (input && input.value) {
            localStorage["curr_player_name"] = input.value
        } else {
            localStorage["curr_player_name"] = "Player 1"
        }
        if (/*gameCycle*/ true) { // FIXME
            // gameCycle.removeKeyListener()
            // UIEditor.clearTetrisField()
        }
        saveRecordToLeaderboard(localStorage["curr_player_name"] )
        // document.getElementById("game_screen").style.display = "none"
        document.getElementById("start_screen").style.display = "none"
        document.getElementById("leaderboard_screen").style.display = "flex"
        let leaderboardList = document.getElementById("leadearboard_list")
        while (leaderboardList.children.length > 0) {
            leaderboardList.removeChild(leaderboardList.children[0])
        }
        let leaderboardStorage = parseMapFromJSON(localStorage["leaderboard"])
        let leaderboardArray = []
        leaderboardStorage.forEach((value, key) => {
            leaderboardArray.push([key, value])
        })
        leaderboardArray.sort((value1, value2) => {
            if (value1[1] > value2[1])
                return -1
            else if (value1[1] < value2[1])
                return 1
            else {
                if (value1[0] > value2[0])
                    return 1
                else if (value1[0] < value2[0])
                    return -1
                else
                    return 0
            }
        })
        ScreenScript.#addAllRowsToLeaderboard(leaderboardArray, leaderboardList);
    }

    static #prepareText(text, maxCharacterInText) {
        let newText = `${text}`.trim()
        if (newText.length > maxCharacterInText)
            newText = newText.slice(0, maxCharacterInText).concat("...")
        return newText
    }

    static #prepareScreen() {
        document.getElementById("current_level").textContent = `Уровень: ${"1"}` // FIXME
        document.getElementById("player_score").textContent = `Счёт: ${"10"}` // FIXME
        document.getElementById("player_name").textContent = ScreenScript.#prepareText(
            "Игрок: " + localStorage["curr_player_name"],
            ScreenScript.maxCharacterInNickForGameScreen
        )
    }

    static #addAllRowsToLeaderboard(leaderboardArray, leaderboardList) {
        for (let i = 0; i < leaderboardArray.length; i++) {
            let nicknameField = document.createElement("div")
            nicknameField.className = "two-column-row-item-left"
            let scoreField = document.createElement("div")
            scoreField.className = "two-column-row-item-right"
            let listRow = document.createElement("div")
            listRow.className = "two-column-row"
            nicknameField.innerText = ScreenScript.#prepareText(leaderboardArray[i][0], ScreenScript.maxCharacterInNickForLeaderboardScreen)
            scoreField.innerText = leaderboardArray[i][1]
            if (leaderboardArray[i][0] === localStorage["curr_player_name"]) {
                nicknameField.style.background = "#21e1ab"
                scoreField.style.background = "#21e1ab"
            } else {
                nicknameField.style.background = "#e1e4e6"
                scoreField.style.background = "#e1e4e6"
            }
            scoreField.style.textAlign = "center"
            listRow.appendChild(nicknameField)
            listRow.appendChild(scoreField)
            leaderboardList.appendChild(listRow)
        }
    }
}
