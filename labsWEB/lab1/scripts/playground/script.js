function edit() {
    let handler = {
        set(target, prop, value) {
            target[prop] = value + 1
            console.log(`${value + 1}`)
            return true
        }
    }
    let proxy = new Proxy({value: 0}, handler)
    proxy.value = proxy.value.valueOf()
    document.getElementById("text").textContent = `num: ${proxy.value}`
}

