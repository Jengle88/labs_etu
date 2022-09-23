
function parseMapFromJSON (jsonObject) {
    let parseJson = JSON.parse(jsonObject)
    return new Map(Object.entries(parseJson))
}

function saveRecordToLeaderboard(playerName) {
    if (localStorage.getItem("leaderboard") == null) {
        let leaderboard = new Map() // создание новой таблицы лидеров
        if (gameCycle && gameCycle.gameScoreProxy) {
            leaderboard.set(playerName, gameCycle.gameScoreProxy.score)
        } else {
            leaderboard.set(playerName, 0)
        }
        localStorage["leaderboard"] = JSON.stringify(Object.fromEntries(leaderboard))
    } else {
        let leaderboard = parseMapFromJSON(localStorage["leaderboard"])
        let record = 0
        if (leaderboard.has(playerName))
            record = leaderboard.get(playerName)
        if (gameCycle && gameCycle.gameScoreProxy) {
            leaderboard.set(playerName, Math.max(gameCycle.gameScoreProxy.score, record))
        } else {
            leaderboard.set(playerName, record)
        }
        localStorage["leaderboard"] = JSON.stringify(Object.fromEntries(leaderboard)) // обновление рекорда
    }
}