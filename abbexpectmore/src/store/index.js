import Vue from 'vue';
import Vuex from 'vuex';

Vue.use(Vuex)

const store = new Vuex.Store({
  state: {
    products: [
      {name:'Bone Boi', price: 30},
      {name:'Bone', price: 290},
      {name:'Bo', price: 20}
    ],
    creds: 
      {user: 'a',pass: 'b'}
    ,
    ad_stat: false,
    locked: false,
    connected: false,
  },
  getters:{
    saleProducts: state => {
      var saleProducts = state.products.map(product => {
        return {
            name: product.name,
            price: product.price/2
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
    reducePrice: (state, payload) => {
      state.products.forEach(product => {
      product.price -= payload
   });         
    },
    cred_check: (state, payload) => {
      if (payload == state.creds.user+state.creds.pass){
        state.ad_stat = true
      }
    },
    log_out: (state) => {
      state.ad_stat = false
    },
    lock: (state) => {
      if (state.locked){
        console.log('unlocked')
        state.locked = false
      }else{
        console.log('locked')
        state.locked = true
      }
    },
    connected: (state) => {
      console.log('Connected!')
      state.connected = true
    },
    conn_fail: (state) => {
      console.log('Failed connecting!')
      state.connected = false
    }
  },
  //Actions to async
  actions: {
    reducePrice: (context, payload) => {
      setTimeout(function(){
        context.commit('reducePrice', payload)
      },2000)
    },
    cred_check: (context, payload) => {
      context.commit('cred_check', payload)
    },
    log_out: (context) => {
      context.commit('log_out')
    },
    lock: (context) => {
      context.commit('lock')
    },
    connected: (context) => {
      context.commit('connected')
    },
    conn_fail: (context) => {
      context.commit('conn_fail')
    }
  },
  modules: {
  }
})

export default store
