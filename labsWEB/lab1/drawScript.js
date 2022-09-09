function drawTetrisBorder(context, startX, startY, width, height) {
    context.strokeStyle = "#000000"
    context.beginPath()
    context.rect(startX, startY, width, height)
    context.closePath()
    context.stroke()
}

function drawTetrisGrid(context, startX, startY, width, height, squareSize) {
    context.strokeStyle = "#00000020"
    for (let x = 0; x < width; x += squareSize) {
        for (let y = 0; y < height; y += squareSize) {
            context.beginPath()
            context.rect(startX + x, startY + y, Math.min(squareSize, width - x), Math.min(squareSize, height - y))
            context.closePath()
            context.stroke()
        }
    }
}

function drawTetrisField() {
    let drawingCanvas = document.getElementById('canvas1')
    if (drawingCanvas && drawingCanvas.getContext) {
        let context = drawingCanvas.getContext('2d')
        let offset = 5
        let squareSize = 20
        drawTetrisBorder(context, offset, offset, drawingCanvas.offsetWidth - 2 * offset, drawingCanvas.offsetHeight - 2 * offset)
        drawTetrisGrid(context, offset, offset, drawingCanvas.offsetWidth - 2 * offset, drawingCanvas.offsetHeight - 2 * offset, squareSize)
    }
}