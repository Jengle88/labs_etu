
function parseMapFromJSON (jsonObject) {
    let parseJson = JSON.parse(jsonObject)
    return new Map(Object.entries(parseJson))
}

function saveRecordToLeaderboard(playerName) {
    if (localStorage.getItem("leaderboard") == null) {
        let leaderboard = new Map() // создание новой таблицы лидеров
        if (gameCycle && gameCycle.gameScoreProxy) {
            leaderboard.set(playerName, gameCycle.gameScoreProxy.score)
        }
        localStorage["leaderboard"] = JSON.stringify(Object.fromEntries(leaderboard))
    } else {
        let leaderboard = parseMapFromJSON(localStorage["leaderboard"])
        if (gameCycle && gameCycle.gameScoreProxy) {
            let prevRecord = leaderboard.get<Number>(playerName)
            if (!prevRecord)
                prevRecord = 0
            leaderboard.set(playerName, Math.max(gameCycle.gameScoreProxy.score, prevRecord))
        }
        localStorage["leaderboard"] = JSON.stringify(Object.fromEntries(leaderboard)) // обновление рекорда
    }
}