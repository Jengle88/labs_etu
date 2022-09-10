const drawingCanvas = document.getElementById('tetris_field')

class UIEditor {
    static squareSize = 20
    static drawTetrisGrid(context, width, height, squareSize, gameField) {
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

    static drawTetrisField() {
        if (drawingCanvas && drawingCanvas.getContext) {
            let context = drawingCanvas.getContext('2d')
            gameCycle.createField(drawingCanvas.width / UIEditor.squareSize, drawingCanvas.height / UIEditor.squareSize)
            UIEditor.drawTetrisGrid(context, drawingCanvas.width, drawingCanvas.height, UIEditor.squareSize, gameCycle.gameField)
        }
    }

    static redrawTetrisField() {
        if (drawingCanvas && drawingCanvas.getContext && gameCycle.gameField) {
            let context = drawingCanvas.getContext('2d')
            UIEditor.clearTetrisField()
            UIEditor.drawTetrisGrid(context, drawingCanvas.width, drawingCanvas.height, UIEditor.squareSize, gameCycle.gameField)
        }
    }

    static clearTetrisField() {
        if (drawingCanvas && drawingCanvas.getContext) {
            let context = drawingCanvas.getContext('2d')
            context.clearRect(0, 0, drawingCanvas.width, drawingCanvas.height)
        }
    }
}

