MRuby::Gem::Specification.new('mruby-gd') do |spec|
  spec.license = 'MIT'
  spec.author  = 'qtakamitsu'
  spec.summary = 'GD Graphics Library for mruby'
  library_paths = `pkg-config --libs-only-L gdlib`.chomp
  spec.linker.library_paths << library_paths unless library_paths.empty?
  spec.linker.libraries << 'gd'
end
