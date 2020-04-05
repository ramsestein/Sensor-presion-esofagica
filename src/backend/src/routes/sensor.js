const Router     = require('express-promise-router');
const db         = require('../db');
const { logger } = require('./../util/logger');
const queries    = require('./../queries');
const config     = require('config');
const { check }  = require('./../util/requestChecker');

const router   = new Router();
module.exports = router;

router.post('/', async (req, res) => {
  try {
    if (!check(req.body, ['type', 'auth_id'])) {
      throw 'bad request for endpoint, mandatory: type, auth_id';
    }
    const response = await db.query(queries.sensor.create,[req.body.type, req.body.auth_id]);
    req.body.id = response.rows[0].id;
    res.status(200).send(JSON.stringify(req.body));
  } catch (e) {
    logger.error(e);
    res.status(500).send(e);
  }
});

router.delete('/:id', async (req, res) => {
  try {
    const { id } = req.params;
    await db.query(queries.sensor.delete,[id]);
    res.status(200).send({deleted: id});
  } catch (e) {
    logger.error(e);
    res.status(500).send(e);
  }
});

router.get('/', async (req, res) => {
  try {
    const { id } = req.params;
    var   page   = req.query.page;
    var   limit  = parseInt(config.get('database.query.limit'));

    var   result       = await db.query(queries.util.count);
    const totalRecords = parseInt(result.rows[0].count);
    const totalPages   = Math.ceil(totalRecords/limit);
    var currentPage    = 1;
    var offset         = 0;

    if (!check(req.query, ['page'])) {
      limit = 0
      result = await db.query(queries.sensor.readUnlimited);
    } else {
      var page = parseInt(req.query.page);
      if (page > totalPages) {
        res.status(400).send(`Requested page ${page} over total pages ${totalPages}`);
      } else {
        offset = limit * (page -1)
        currentPage = page;
        result = await db.query(queries.sensor.read, [offset, limit]);
      }
    }

    response = {
      offset:       offset,
      limit:        limit,
      currentPage:  currentPage,
      totalPages:   totalPages,
      totalRecords: totalRecords,
      result:       result.rows,
    };

    res.status(200).send(JSON.stringify(response));
  } catch (e) {
    logger.error(e);
    res.status(500).send(e);
  }
});

router.get('/:id', async (req, res) => {
  try {
    const { id } = req.params;
    const result = await db.query(queries.sensor.getById, [id]);
    res.status(200).send(JSON.stringify(result.rows));
  } catch (e) {
    logger.error(e);
    res.status(500).send(e);
  }
});

router.put('/:id', async (req, res) => {
  try {
    if (!check(req.body, ['type', 'auth_id'])) {
      throw 'bad request for endpoint, mandatory: type, auth_id';
    }
    const { id } = req.params;
    const result = await db.query(queries.sensor.update, [req.body.type, req.body.auth_id, id]);
    res.status(200).send({updated: id});
  } catch (e) {
    logger.error(e);
    res.status(500).send(e);
  }
});
