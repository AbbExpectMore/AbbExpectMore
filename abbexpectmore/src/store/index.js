import Vue from 'vue';
import Vuex from 'vuex';
import axios from 'axios'

Vue.use(Vuex)

const store = new Vuex.Store({
  state: {
    creds: {
      user: "",
      pass: ""
    },
    ad_stat: false,
    locked: false,
    sends: {
      method: 'ctrl',
      value: '',
      id: ''
    },
    info: undefined,
    onOff: false,
    lk: {
      id: undefined,
      action: 'lock',
      value: undefined
    },
    rgb: '(0,0,0)',
    loading: false,
    tried_once: false
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
      axios
        .put('https://ec4avk1xoh.execute-api.us-east-1.amazonaws.com/v1/', payload)
        .then(respons => {
          state.info = respons.data
          // console.log(state.info.success)
          state.loading = false
          state.tried_once = true
          if (state.info.success) {
            state.ad_stat = true
            state.lk.id = state.info.id
          }
        })
    },
    postRGB: (state) => {
      // state.rgb = 'rgb' + String(state.sends.value)
      // console.log(state.sends)
      if (state.ad_stat == true) {
        state.sends.id = state.lk.id
      } else {
        state.sends.id = ""
        state.lk.id = ""
      }
      axios
        .post('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1/change', JSON.stringify(state.sends))
        .then(respons => {
          state.info = respons.data
          state.loading = false
          console.log(state.info)
        })
    },
    locked: (state) => {
      console.log('Hello')
    },
    log_out: (state) => {
      state.ad_stat = false
      state.creds = {
        user: undefined,
        pass: undefined
      }
      state.tried_once = false
    },
    lock: (state) => {
      if (state.locked) {
        state.lk.value = false
        axios
          .post('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1', JSON.stringify(state.lk))
          .then(respons => {
            state.info = respons.data
            // console.log(state.info)
          })
        state.locked = false
      } else {
        // console.log('locked')
        state.lk.value = true
        axios
          .post('https://4f4owrwgp2.execute-api.us-east-1.amazonaws.com/v1', JSON.stringify(state.lk))
          .then(respons => {
            state.info = respons.data
            // console.log(state.info)
          })
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
      context.commit('log_out')
    },
    postRGB: (context) => {
      context.commit('postRGB')
    },
    lock: (context) => {
      context.commit('lock')
    },
    locked: (context) => {
      context.commit('locked')
    },
  }
})

export default store