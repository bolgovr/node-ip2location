{
  'targets': [
    {
      'target_name': 'ip2locationnode',
      'sources': [ 'src/ip2locationnode.cc' ],
      'link_settings': {
          'libraries': [
              '-lIP2Location'
          ]
      }
    }
  ]
}


