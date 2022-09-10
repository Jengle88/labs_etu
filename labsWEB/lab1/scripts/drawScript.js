const drawingCanvas = document.getElementById('tetris_field')

function drawTetrisGrid(context, width, height, squareSize, gameField) {
    context.strokeStyle = "#00000020"
    for (let x = 0; x < width; x += squareSize) {
        for (let y = 0; y < height; y += squareSize) {
            context.beginPath()
            context.fillStyle = gameField.field[y / squareSize][x / squareSize]
            context.fillRect(x, y, Math.min(squareSize, width - x), Math.min(squareSize, height - y))
            context.strokeRect(x, y, Math.min(squareSize, width - x), Math.min(squareSize, height - y))
            context.closePath()
            context.stroke()
        }
    }
}

function drawTetrisField() {
    if (drawingCanvas && drawingCanvas.getContext) {
        let context = drawingCanvas.getContext('2d')
        let squareSize = 20
        gameCycle.createField(drawingCanvas.width / squareSize, drawingCanvas.height / squareSize)
        drawTetrisGrid(context, drawingCanvas.width, drawingCanvas.height, squareSize, gameCycle.gameField)
    }
}

function clearTetrisField() {
    if (drawingCanvas && drawingCanvas.getContext) {
        let context = drawingCanvas.getContext('2d')
        context.clearRect(0, 0, drawingCanvas.width, drawingCanvas.height)
    }
}