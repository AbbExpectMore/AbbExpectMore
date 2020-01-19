import Vue from 'vue';
import Vuex from 'vuex';
import axios from 'axios'

Vue.use(Vuex)

const store = new Vuex.Store({
  state: {
    creds:
      { user: 'a', pass: 'b' }
    ,
    ad_stat: false,
    locked: false,
    sends: {
      method: 'ctrl',
      value: '',
      pass: 'okokokok'
    },
    info: undefined,
    onOff: false,
  },
  getters: {
    saleProducts: state => {
      var saleProducts = state.products.map(product => {
        return {
          name: product.name,
          price: product.price / 2
        }
      })
      return saleProducts
    },
    ad_stat: state => {
      var status = state.ad_stat
      return status
    }
  },
  mutations: {
    cred_check: (state, payload) => {
      if (payload == state.creds.user + state.creds.pass) {
        state.ad_stat = true
      }
    },
    postRGB: (state) => {
      axios
        .post('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/change', JSON.stringify(state.sends))
        .then(respons => {
          state.info = respons.data
          console.log(state.info)
        })
    },
    log_out: (state) => {
      state.ad_stat = false
    },
    lock: (state) => {
      if (state.locked) {
        // console.log('unlocked')
        state.locked = false
      } else {
        // console.log('locked')
        state.locked = true
      }
    },
  },
    //Actions to async
    actions: {
      cred_check: (context, payload) => {
        context.commit('cred_check', payload)
      },
      log_out: (context) => {
        context.commit('postRGB')
      },
      postRGB: (context) => {
        context.commit('postRGB')
      },
      lock: (context) => {
        context.commit('lock')
      },
    }
  })

export default store
