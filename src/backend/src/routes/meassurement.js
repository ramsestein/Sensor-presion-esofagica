const Router = require('express-promise-router')
const db     = require('../db')

const router = new Router()
module.exports = router

//TODO: checks params and filter in case that is missing access_token
// and filter stranger things as NaN
router.post('/:id', async (req, res) => {
  try {
    const { id } = req.params
    await db.query(`INSERT INTO meassurement (spo2, ppm, batt, sequence, id_sensor) VALUES (${req.body.spo2}, ${req.body.ppm}, ${req.body.batt}, ${req.body.sequence}, ${id})`)
    res.send('ok')
  } catch (e) {
    console.error(e)
    res.status(500).send(e)
  }
})
