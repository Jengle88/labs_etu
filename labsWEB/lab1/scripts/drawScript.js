class UIEditor {
    static squareSize = 20
    static clearElemColor = "#00000020"
    static fieldCanvas = document.getElementById("tetris_field")
    static previewCanvas = document.getElementById("next_figure_canvas")

    static #drawTetrisGrid(context, width, height, squareSize, gameField) {
        context.strokeStyle = UIEditor.clearElemColor
        for (let x = 0; x < width; x += squareSize) {
            for (let y = 0; y < height; y += squareSize) {
                context.beginPath()
                context.fillStyle = gameField[y / squareSize][x / squareSize]
                context.fillRect(x, y, Math.min(squareSize, width - x), Math.min(squareSize, height - y))
                context.strokeRect(x, y, Math.min(squareSize, width - x), Math.min(squareSize, height - y))
                context.closePath()
                context.stroke()
            }
        }
    }

    static drawTetrisField(canvas = UIEditor.fieldCanvas, field = gameCycle.gameField.field) {
        if (canvas && canvas.getContext) {
            let context = canvas.getContext('2d')
            UIEditor.#drawTetrisGrid(context, canvas.clientWidth, canvas.clientHeight, UIEditor.squareSize, field)
        }
    }

    static redrawTetrisField(canvas = UIEditor.fieldCanvas, field = gameCycle.gameField.field) {
        if (canvas && canvas.getContext && field) {
            let context = canvas.getContext('2d')
            UIEditor.clearTetrisField(canvas)
            UIEditor.#drawTetrisGrid(context, canvas.clientWidth, canvas.clientHeight, UIEditor.squareSize, field)
        }
    }

    static clearTetrisField(canvas = UIEditor.fieldCanvas) {
        if (canvas && canvas.getContext) {
            let context = canvas.getContext('2d')
            context.clearRect(0, 0, canvas.clientWidth, canvas.clientHeight)
        }
    }

    static drawPreviewTetramino(nextTetramino) {
        if (UIEditor.previewCanvas && UIEditor.previewCanvas.getContext) {
            let field = []
            for (let i = 0; i < UIEditor.previewCanvas.clientHeight / this.squareSize; i++) {
                field.push([])
                for (let j = 0; j < UIEditor.previewCanvas.clientWidth / this.squareSize; j++) {
                    field[i].push(UIEditor.clearElemColor)
                }
            }
            let prevXCoords = nextTetramino.xRotatePoint
            nextTetramino.xRotatePoint = 2
            nextTetramino.drawOnField(field)
            nextTetramino.xRotatePoint = prevXCoords
            UIEditor.redrawTetrisField(UIEditor.previewCanvas, field)
        }
    }
}

